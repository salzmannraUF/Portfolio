import numpy as np
from RLalgs.utils import action_evaluation

def policy_iteration(env, gamma, max_iteration, theta):
    """
    Implement Policy iteration algorithm.

    Inputs:
    env: OpenAI Gym environment.
            env.P: dictionary
                    P[state][action] is list of tuples. Each tuple contains probability, nextstate, reward, terminal
                    probability: float
                    nextstate: int
                    reward: float
                    terminal: boolean
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
    """

    V = np.zeros(env.nS)
    policy = np.zeros(env.nS, dtype = np.int32)
    policy_stable = False
    numIterations = 0
    
    while not policy_stable and numIterations < max_iteration:
        #Implement it with function policy_evaluation and policy_improvement
        ############################
        # YOUR CODE STARTS HERE

        V = policy_evaluation(env, policy, gamma, theta) #policy eval
        policy, policy_stable = policy_improvement(env, V, policy, gamma) # policy improve

        # YOUR CODE ENDS HERE
        ############################
        numIterations += 1
        
    return V, policy, numIterations


def policy_evaluation(env, policy, gamma, theta):
    """
    Evaluate the value function from a given policy.

    Inputs:
    env: OpenAI Gym environment.
            env.P: dictionary
                    
            env.nS: int
                    number of states
            env.nA: int
                    number of actions

    gamma: float
            Discount factor.
    policy: numpy.ndarray
            The policy to evaluate. Maps states to actions.
    theta: float
            The threshold of convergence.
    
    Outputs:
    V: numpy.ndarray
            The value function from the given policy.
    """
    ############################
    # YOUR CODE STARTS HERE

    V = np.zeros(env.nS) # initalize state values
    delta = 1 #just initialize to get in the loop
    while delta >= theta: #until delta is less than theta
      delta = 0  # set delta to zero
      for s in range(env.nS): # for each state in num of state
        temp = V[s]  # set temp to current V[s]
        a = policy[s]  # set the action to the policy of the current state
        V[s] = sum(env.P[s][a][i][0]*(env.P[s][a][i][2] + gamma*V[env.P[s][a][i][1]]) for i in range(len(env.P[s][a])))
        #sum of probability * reward and next state value * discount factor for each tuple
        delta = max(delta,abs(temp - V[s])) #update delta value to be max of current delta and diff between old and new V[s]

    # YOUR CODE ENDS HERE
    ############################

    return V


def policy_improvement(env, value_from_policy, policy, gamma):
    """
    Given the value function from policy, improve the policy.

    Inputs:
    env: OpenAI Gym environment
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

    value_from_policy: numpy.ndarray
            The value calculated from the policy
    policy: numpy.ndarray
            The previous policy.
    gamma: float
            Discount factor.

    Outputs:
    new policy: numpy.ndarray
            An array of integers. Each integer is the optimal action to take
            in that state according to the environment dynamics and the
            given value function.
    policy_stable: boolean
            True if the "optimal" policy is found, otherwise false
    """
    ############################
    # YOUR CODE STARTS HERE

    policy_stable = True # set policy stable True
    for s in range(env.nS):  # for each state in num of states
        temp_policy = policy[s] # set temp to current policy
        max_a = np.zeros(4) # set a list of values equal to 0 to update with new policies
        temp = 0 # set a temp for new policy values
        for a in range(env.nA):
            temp = sum(env.P[s][a][i][0]*(env.P[s][a][i][2] + gamma*value_from_policy[env.P[s][a][i][1]]) for i in range(len(env.P[s][a])))
            max_a[a] = temp
        new_policy = np.argmax(max_a) # from policies from each action, choose best
        if new_policy != temp_policy: # if best is not equal to past
            policy[s] = new_policy # set new policy
            policy_stable = False # set policy stable to false
            
    # YOUR CODE ENDS HERE
    ############################

    return policy, policy_stable