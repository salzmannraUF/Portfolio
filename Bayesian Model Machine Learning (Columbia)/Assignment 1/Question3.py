# Raymond Salzmann
# Bayesian Model Machine Learning Homework 1
# Question 2 (Gibbs Sampling Algorithm)
# Date Due: 10/11/2020

import numpy as np
import pandas as pd
from sklearn.metrics import confusion_matrix
from matplotlib import pyplot as plt

data = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\ratings.csv', names=['user_id', 'movie_id', 'ratings'])


def SampleV(Ij,dim,sigma,df,cov):
    csum = 0
    for i in range(len(df)):
        vj = np.reshape(Ij[:,data['movie_id'].iloc[i]],(5,1))
        csum += df['ratings'].iloc[i]*vj

    return np.reshape(np.random.multivariate_normal(np.reshape((1/(sigma ** 2))*np.dot(cov,csum),(dim,)),cov),(1,dim))


def SampleU(Ini,dim,sigma,df,cov):
    csum = 0
    if len(df > 0):
        for i in range(len(df)):
            ui = np.reshape(Ini[:,data['user_id'].iloc[i]],(5,1))
            csum += df['ratings'].iloc[i]*ui
    else:
        csum = np.zeros((5, 1),dtype=np.float32)

    return np.reshape(np.random.multivariate_normal(np.reshape((1/(sigma**2))*np.dot(cov,csum),(dim,)),cov),(1,dim))


def covar_mat(cov_in,sigma,dim,c):
    return np.linalg.inv(((1/c)*np.identity(dim)+(1/sigma**2)*(np.dot(cov_in,cov_in.T))))


def log_likelihood(U,V,R,sigma,c):
    return np.sum((-1/(2*(sigma**2)))*np.dot((R-np.dot(U.T,V)).T,(R-np.dot(U.T,V))))+np.sum((-1/(2*c))*np.dot(U.T,U))+np.sum((-1/(2*c))*np.dot(V.T,V))


def Expectation(U,V):
    return (1/1000)*np.dot(U.T, V)


def Gibbs_Algo(movie, user, dim, data, R):
    U = np.zeros((dim,user),dtype=np.float32)
    V = np.zeros((dim,movie),dtype=np.float32)
    like = []
    esum = np.zeros((user,movie),dtype=np.float32)

    for e in range(1000):
        covV = covar_mat(V, 1, dim, 1)
        sampleV = []
        sampleU = []
        for i in range(user):
            df = data[data['user_id'] == (i+1)]
            sampleV.append(SampleV(V,dim,1,df,covV))
        sampleV = np.reshape(np.array(sampleV),(user,dim))
        U = sampleV.T

        covU = covar_mat(U, 1, dim, 1)
        for i in range(movie):
            df = data[data['movie_id'] == (i + 1)]
            sampleU.append(SampleU(U,dim,1,df,covU))
        sampleU = np.reshape(np.array(sampleU),(movie,dim))
        V = sampleU.T

        like.append(log_likelihood(U,V,R,1,1))
        print(e)
        if (e + 1) % 25 == 0:
            esum += np.dot(U.T,V)

    return U, V, like, esum


def predict(test,expec):
    result = np.zeros((len(test),1),dtype=np.float32)
    for i in range(len(test)):
        movie = test.iloc[i]['movie_id']
        user = test.iloc[i]['user_id']
        csum = expec[user-1][movie-1]/40
        if csum > 0:
            csum = 1
        else:
            csum = -1
        result[i:i+1,:] = csum

    return result


def main():
    with open(r'C:\Users\\raymo\Desktop\ML\Homework1\\movies.txt', 'r') as doc:
        movies = doc.read()

    movie_names = movies.split('\n')

    data_test = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\ratings_test.csv',names=['user_id', 'movie_id', 'ratings'])
    R = pd.read_csv(r'C:\Users\\raymo\Desktop\ML\Homework1\\useful_layout.csv')
    R2 = np.array(R)
    R2 = R2[:, 1:]

    movie = len(movie_names[1:])  # number of unique movies users can rate
    user = len(np.unique(data['user_id']))  # number of unique users
    dim = 5

    U, V, Likelihood, expectation_sum = Gibbs_Algo(movie, user, dim, data, R2)

    x_axis = np.arange(1, 1001)
    plt.plot(x_axis, Likelihood)
    plt.xlabel("Iteration")
    plt.title("Log Joint Likelihood for all iterations")

    plt.plot(x_axis[::100], Likelihood[::100])
    plt.xlabel("Iteration")
    plt.title("Log Joint Likelihood for iterations 100 to 1000")

    test_r = np.array(data_test['ratings'])
    test_r = test_r.astype(np.float32)
    esum = np.dot(U.T,V)
    predicted = predict(data_test,esum)
    predicted = np.reshape(predicted,(len(data_test),))
    cm = confusion_matrix(test_r,predicted)
    print(cm)

main()
