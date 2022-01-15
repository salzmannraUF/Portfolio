import numpy as np
from RLalgs.utils import action_evaluation

def value_iteration(env, gamma, max_iteration, theta):
    """
    Implement value iteration algorithm. 

    Inputs:
    env: OpenAI Gym environment.
            env.P: dictionary
                    the transition probabilities of the environment
                    P[state][action] is list of tuples. Each tuple contains probability, nextstate, reward, terminal
            env.nS: int
                    number of states
            env.nA: int
                    number of actions
    gamma: float
            Discount factor.
    max_iteration: int
            The maximum number of iterations to run before stopping.
    theta: float
            The threshold of convergence.
    
    Outputs:
    V: numpy.ndarray
    policy: numpy.ndarray
    numIterations: int
            Number of iterations
    """

    V = np.zeros(env.nS)
    numIterations = 0

    #Implement the loop part here
    ############################
    # YOUR CODE STARTS HERE

    delta = 1 # set delta to anything to get into the loop
    while numIterations < max_iteration or delta >= theta: # loop while delta isnt < theta and while below max_iteration
      delta = 0 # reset delta to zero for loop
      for s in range(env.nS): # for state in states
          temp = V[s] # set temp equal to the state value
          max_a = np.zeros(4) # initalize action array for state val based on actions
          new_val = 0 # initailize the policy value to 0
          for a in range(env.nA):
              new_val = sum([env.P[s][a][i][0]*(env.P[s][a][i][2] + gamma*V[env.P[s][a][i][1]]) for i in range(len(env.P[s][a]))])
              # calculate state value by sum of probability * reward and next state value * discount factor
              max_a[a] = new_val # replace the 0 in the list with the calculated policy value
          V[s] = max(max_a) # take the max of the list to find the new max state value
          delta = max(delta,abs(temp-V[s])) # calculate new delta
      numIterations += 1  #iterate to make sure we're under max iterations

    # YOUR CODE ENDS HERE
    ############################
    
    #Extract the "optimal" policy from the value function
    policy = extract_policy(env, V, gamma)
    
    return V, policy, numIterations

def extract_policy(env, v, gamma):

    """ 
    Extract the optimal policy given the optimal value-function.

    Inputs:
    env: OpenAI Gym environment.
            env.P: dictionary
                    P[state][action] is tuples with (probability, nextstate, reward, terminal)
                    probability: float
                    nextstate: int
                    reward: float
                    terminal: boolean
            env.nS: int
                    number of states
            env.nA: int
                    number of actions
    v: numpy.ndarray
        value function
    gamma: float
        Discount factor. Number in range [0, 1)
    
    Outputs:
    policy: numpy.ndarray
    """

    policy = np.zeros(env.nS, dtype = np.int32)
    ############################
    # YOUR CODE STARTS HERE

    for s in range(env.nS):
      policy_val = np.zeros(4) # create blank list for each action to find policy
      for a in range(env.nA):
          policy_val[a] = (sum(env.P[s][a][i][0]*(env.P[s][a][i][2] + gamma*v[env.P[s][a][i][1]]) for i in range(len(env.P[s][a]))))
          # calculate the policy values for each action
      policy[s] = np.argmax(policy_val)
      # find the best policy value and save it as optimal policy

    # YOUR CODE ENDS HERE
    ############################

    return policy