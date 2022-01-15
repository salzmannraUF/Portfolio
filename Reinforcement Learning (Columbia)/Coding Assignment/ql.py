import numpy as np
from RLalgs.utils import epsilon_greedy
import random

def QLearning(env, num_episodes, gamma, lr, e):
    """
    Implement the Q-learning algorithm following the epsilon-greedy exploration.

    Inputs:
    env: OpenAI Gym environment 
            env.P: dictionary
                    P[state][action] are tuples of tuples tuples with (probability, nextstate, reward, terminal)
                    probability: float
                    nextstate: int
                    reward: float
                    terminal: boolean
            env.nS: int
                    number of states
            env.nA: int
                    number of actions
    num_episodes: int
            Number of episodes of training
    gamma: float
            Discount factor.
    lr: float
            Learning rate.
    e: float
            Epsilon value used in the epsilon-greedy method.

    Outputs:
    Q: numpy.ndarray
    """

    Q = np.zeros((env.nS, env.nA))
    
    #TIPS: Call function epsilon_greedy without setting the seed
    #      Choose the first state of each episode randomly for exploration.
    ############################
    # YOUR CODE STARTS HERE

    for i in range(num_episodes):
      s = np.random.randint(0,env.nS) # set a random state between 0 and num states
      isd = [] # perpare an array to be used in the env.isd
      for i in range(env.nS):
        if i == s:
          isd.append(1)
        else:
          isd.append(0)
      env.isd = isd # isd for the model
      env.reset() # reset the game to 0
      finish = False
      while finish == False:
          a = epsilon_greedy(Q[s], e) # epsilon greedy for action
          next_s, r, finish, P = env.step(a) # find the rest through step
          new_val = (1-lr)*Q[s,a]+lr*(r+gamma*np.max(Q[next_s]))
          # compute the new q value to be put in the overall Q
          Q[s,a] = new_val # add the calculated value to Q
          s = next_s # iterate the state from curent to the next found from env.step earlier

    # YOUR CODE ENDS HERE
    ############################

    return Q