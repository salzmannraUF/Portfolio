# Raymond Salzmann
# Bayesian Model Machine Learning Homework 1
# Question 2 (Expectation Maximization Algorithm)
# Date Due: 10/11/2020

import numpy as np
from matplotlib import pyplot as plt
import pandas as pd
from scipy.stats import norm
from sklearn.metrics import confusion_matrix


def pon(array,p,n):
    if array == -1:
        array = n
    elif array == 1:
        array = p
    else:
        array = array

    return array


def JointDistribution(U,V,sigma,dim,vec,R):
    first = (dim*np.log(2*np.pi))+(np.sum(np.dot(U.T,U))+np.sum(np.dot(V.T,V)))
    second = np.log(np.sum((vec(R,norm.cdf(np.dot(U.T,V)/sigma),(1-norm.cdf(np.dot(U.T,V)/sigma))))))
    result = first + second

    return result


def expectation(U,V,sigma):
    neg_expec = -(norm.pdf(-np.dot(U.T,V)/sigma)/norm.cdf(-np.dot(U.T,V)/sigma))
    pos_expec = norm.pdf(-np.dot(U.T,V)/sigma)/(1-norm.cdf(-np.dot(U.T,V)/sigma))

    return neg_expec,pos_expec


def maxU(V,ef,sigma,c):
    return np.dot(np.linalg.inv(((np.identity(5)/c)+np.dot(V,V.T)/sigma**2)),np.dot(V,ef.T))/sigma**2


def maxV(U,ef,sigma,c):
    return np.dot(np.linalg.inv(((np.identity(1)/c)+np.dot(U,U.T)/sigma**2)),np.dot(U,ef))/sigma**2


def EMAlgorithm(user,movie,dim,R,sigma,c):
    vec = np.vectorize(pon)
    joint = []
    U = np.random.multivariate_normal(np.zeros((dim,)),0.1*np.identity(dim),size=(user,))
    U = U.T
    V = np.random.multivariate_normal(np.zeros((dim,)),0.1*np.identity(dim,), size=(movie,))
    V = V.T
    for e in range(100):

        neg_expec,pos_expec = expectation(U,V,sigma)  # Estep for U
        of = vec(R,pos_expec,neg_expec)
        ef = np.dot(U.T,V)+of
        U = maxU(V,ef,sigma,c)  # Mstep for U

        neg_expec,pos_expec = expectation(U,V,sigma)  # Estep for V
        of = vec(R, pos_expec, neg_expec)
        ef = np.dot(U.T, V) + of
        V = maxV(U, ef, sigma, c)  # Mstep for V

        joint_dis = JointDistribution(U, V, sigma, dim, vec, R)  # calc log joint likelihood
        print(joint_dis)
        joint.append(joint_dis)  # append the last calculated value to a list of all values

    print("DONE!")

    return U, V, joint


def predict(test,expec):
    result = np.zeros((len(test),1),dtype=np.float32)
    for i in range(len(test)):
        user = test.iloc[i]['user_id']
        movie = test.iloc[i]['movie_id']

        csum = expec[user - 1][movie - 1] / 40
        if csum > 0:
            csum = 1
        else:
            csum = -1
        result[i:i + 1, :] = csum
    return result


def main():
    data = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\ratings.csv', names=['user_id', 'movie_id', 'ratings'])
    with open(r'C:\Users\\raymo\Desktop\ML\Homework1\\movies.txt','r') as doc:
        movies = doc.read()

    movie_names = movies.split('\n')

    data_test = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\ratings_test.csv', names=['user_id', 'movie_id', 'ratings'])
    R = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\useful_layout.csv')  # a csv i made that makes the data more readable
    R2 = np.array(R)
    R2 = R2[:, 1:]

    movie = len(movie_names[1:])  # number of unique movies users can rate
    user = len(np.unique(data['user_id']))  # number of unique users
    dim = 5
    sigma = 1
    c = 1

    U, V, JD = EMAlgorithm(user, movie, dim, R2, sigma, c)
    U1, V1, JD1 = EMAlgorithm(user, movie, dim, R2, sigma, c)
    U2, V2, JD2 = EMAlgorithm(user, movie, dim, R2, sigma, c)
    U3, V3, JD3 = EMAlgorithm(user, movie, dim, R2, sigma, c)
    U4, V4, JD4 = EMAlgorithm(user, movie, dim, R2, sigma, c)
    U5, V5, JD5 = EMAlgorithm(user, movie, dim, R2, sigma, c)

    x_axis = np.arange(100)
    plt.plot(x_axis, JD)
    plt.xlabel("Iteration")
    plt.title("Log Joint Likelihood  ln p(R,U,V)")

    line1, = plt.plot(x_axis[20:], JD1[20:], label='OF1')
    line2, = plt.plot(x_axis[20:], JD2[20:], label='OF2')
    line3, = plt.plot(x_axis[20:], JD3[20:], label='OF3')
    line4, = plt.plot(x_axis[20:], JD4[20:], label='OF4')
    line5, = plt.plot(x_axis[20:], JD5[20:], label='OF5')
    plt.xlabel("Iteration")
    plt.title('Objective Functions with random starting points')
    plt.legend(handles=[line1, line2, line3, line4, line5])
    plt.show()

    test_r = np.array(data_test['ratings'])
    test_r = test_r.astype(np.float32)
    esum = np.dot(U.T,V)
    predicted = predict(data_test, esum)
    predicted = np.reshape(predicted, (len(data_test),))
    cm = confusion_matrix(test_r, predicted)
    print(cm)

main()