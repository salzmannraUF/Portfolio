import numpy as np
from RLalgs.utils import epsilon_greedy
import random

def SARSA(env, num_episodes, gamma, lr, e):
    """
    Implement the SARSA algorithm following epsilon-greedy exploration.

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
            State-action values
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
      a = epsilon_greedy(Q[s],e)
      while finish == False: # this will all be relatively similar to Qlearning
          next_s, r, finish, p = env.step(a) # get the next state, reward and finish from env.step from current action from ep greedy
          next_a = epsilon_greedy(Q[next_s],e) # find next action from next state from ep greedy
          next_Q = Q[next_s,next_a] # save the next Q value in to the current Q array
          val = (1-lr)*Q[s,a]+lr*(r+gamma*next_Q) # calculate the state value for the next q and the lr
          Q[s,a] = val # add the calculated Q value into the current Q array
          s,a = next_s, next_a  # iterate both the state and action values and run the loop again assuming finish isn't True

    # YOUR CODE ENDS HERE
    ############################

    return Q