import argparse
import numpy as np
import os
import random
import time
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from cartpole_env import configure_pybullet, make_cart_pole_env
from network import Network
from replay import Replay


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--seed', type=int, default=1,
                        help='seed of the experiment')
    parser.add_argument('--save_dir', type=str, default='models',
                        help="the root folder for saving the checkpoints")
    parser.add_argument('--gui', action='store_true', default=False,
                        help="whether to turn on GUI or not")
    args = parser.parse_args()
    args.timestr = time.strftime("%Y-%m-%d_%H-%M-%S")
    args.save_dir = os.path.join(args.save_dir, args.timestr)
    if not args.seed:
        args.seed = int(time.time())
    return args


def train(env, args, device):
    # set up seed
    random.seed(args.seed)
    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    torch.backends.cudnn.deterministic = False
    env.seed(args.seed)
    env.action_space.seed(args.seed)
    env.observation_space.seed(args.seed)
    
    # initialize: action network Q_A with random weights; target network Q_T = Q_A
    Q_A = Network(env)
    Q_T = Network(env)
    Q_T.load_state_dict(Q_A.state_dict())
    Q_T.eval()
    
    # initialize: replay memory D with capacity N
    N = 10000
    D = Replay(N)
    
    # hyperparameters
    num_episodes = 1000
    T = 500
    batch_size = 32
    gamma = 0.999
    eps = 1.0
    eps_min = 0.01
    eps_decay = 0.95
    
    learning_rate = 0.0001
    optimizer = torch.optim.Adam(Q_A.parameters(), lr = learning_rate)
    criterion = nn.MSELoss()
    
    device = torch.device('cpu')
    
    for episode in range(num_episodes):
        print("episode ", episode, '\t', end = '')
        
        # initialize: episode_reward = 0; reset the environment and obtain the first observation s_1
        episode_reward = 0
        init_state = env.reset()
        state = init_state
        
        for t in range(T):
            # with probability eps, a_t = random; otherwise a_t = max_a(Q_A(s_t, a))
            if np.random.random() <= eps:
                #print("picked random action")
                action = env.action_space.sample()
            else:
                #print("picked forward function")
                #print("Q_A.forward:\n", Q_A(state, device))
                action = np.argmax(Q_A(state, device).detach().numpy())
            #print("eps: ", eps, '\t', end = '')
            #print("action: ", action)
            
            # execute a_t and observe r_t+1, s_t+1
            next_state, reward, done, _ = env.step(action)
            #print("next_state:\n", next_state)
            #print("reward:\n", reward)
            #print("done:\n", done)
                
            # episode reward += r_t+1
            episode_reward += reward
            
            # store transition (s_t, a_t, r_t+1, s_t+1) in D (remove old data if needed)
            transition = [state, action, reward, next_state, done]
            D.put(transition)
            
            # train network:
            #     sample random minibatch of transitions from D
            #     perform batch GD on Q_A with L = F(Q_A(s_t, a_t) - [r_t+1 + gamma*max_a(Q_T(s_t+1, a))])
            if len(D.buffer) > batch_size:
                #print("training")
                Q_A.train()
                
                state_batch, action_batch, reward_batch, next_state_batch, done_batch = D.sample(batch_size)
                action_batch = torch.tensor(action_batch, dtype = torch.int64)
                #print("state_batch:\n", state_batch)
                #print("action_batch:\n", action_batch)
                #print("reward_batch:\n", reward_batch)
                #print("next_state_batch:\n", next_state_batch)
                #print("done_batch:\n", done_batch)
                
                # first term
                #print("Q_A:\n", Q_A(state_batch, device))
                q_a = Q_A(state_batch, device)
                q_a = torch.gather(q_a, 1, action_batch.view((-1,1))).view(-1)
                #print("q_a:\n", q_a)
                
                # second term
                #print("Q_T:\n", Q_T(next_state_batch, device))
                q_t = Q_T(next_state_batch, device).detach().numpy()
                q_t = reward_batch + gamma*np.amax(q_t, axis = 1)*(1 - done_batch)
                #print("q_t:\n", q_t)
                q_t = torch.tensor(q_t, dtype = torch.float32, requires_grad = True)
                #print("q_t:\n", q_t)
                
                # gradient descent
                optimizer.zero_grad()
                loss = criterion(q_a, q_t)
                loss.backward()
                nn.utils.clip_grad_norm(list(Q_A.parameters()), 0.5)
                optimizer.step()
                
                # reduce epsilon
                if eps > eps_min:
                    eps *= eps_decay
            
            # set s_t = s_t+1
            state = next_state
            
            # if s_t+1 is terminal: break (end episode)
            if done:
                break
        
        # report episode reward and save checkpoint of Q_A if reward is higher than threshold R
        print("reward: ", episode_reward)
        
        R = T
        if episode_reward >= R:
            model_folder_name = f'episode_{episode:06d}_reward_{round(episode_reward):03d}'
            if not os.path.exists(os.path.join(args.save_dir, model_folder_name)):
                os.makedirs(os.path.join(args.save_dir, model_folder_name))
            torch.save(Q_A.state_dict(), os.path.join(args.save_dir, model_folder_name, 'network.pth'))
            print(f'model saved to {os.path.join(args.save_dir, model_folder_name, "network.pth")}\n')
        
        # every k episodes: set target network Q_T = Q_A
        k = 3
        if episode % k == 0:
            Q_T.load_state_dict(Q_A.state_dict())
            #print("Target set to action")

if __name__ == "__main__":
    args = get_args()
    configure_pybullet(rendering=args.gui, debug=True)
    env = make_cart_pole_env()
    device = torch.device('cpu')

    train(env, args, device)
