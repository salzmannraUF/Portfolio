# Raymond Salzmann
# Machine Learning Homework 3
# December 13, 2020

import numpy as np
from scipy.stats import binom
from matplotlib import pyplot as plt

def read_csv():
    x = []
    with open(r'C:\Users\raymo\Desktop\ML\Homework3\data.csv') as file:
        data = file.readlines()
        for row in data:
            x.append(int(row.strip()))

    n_data = len(x)
    x = np.array(x)
    x = np.reshape(x,(n_data,1))
    return x,n_data


def plot(x,l1,c1,l2,c2,l3,c3):
    plt.plot(range(50), l1, label='K=3')
    plt.plot(range(50), l2, label='K=9')
    plt.plot(range(50), l3, label='K=15')
    plt.legend()
    plt.xlabel('Iterations')
    plt.ylabel('Log Likelihood')
    plt.title('Log Likelihood for varying Ks vs Iterations')
    plt.show()

    plt.scatter(x, c1)
    plt.title('K = 3')
    plt.show()

    plt.scatter(x, c2)
    plt.title('K = 9')
    plt.show()

    plt.scatter(x, c3)
    plt.title('K = 15')
    plt.show()
    return


def EM(x,K,len_data):
    theta = np.random.rand(K, 1).reshape((K, 1))
    phi = np.zeros([len_data, K])
    pi = np.ones([K,1])/K

    out = []
    clus = []

    for i in range(50):

        for m in range(K):
            phi[:, m] = binom.pmf(x[:, 0], 20, theta[m]) * pi[m]
        temp_phi = np.sum(phi, axis=1)
        temp_phi = temp_phi.reshape([len_data, 1])
        phi /= temp_phi

        nj = np.sum(phi,axis=0)
        theta = np.sum(phi*x,axis=0)/(20*nj)
        pi = nj/len_data

        csum = np.zeros((len_data, 1))
        for n in range(K):
            csum += pi[n] * binom.pmf(x, 20, theta[n])
        out.append(np.sum(np.log(csum)))

    for j in range(len_data):
        clus.append(np.argmax(phi[j, :]))

    return out, clus


def main():
    x,n_data = read_csv()

    l1,c1 = EM(x,3,n_data)
    l2,c2 = EM(x,9,n_data)
    l3,c3 = EM(x,15,n_data)

    plot(x,l1,c1,l2,c2,l3,c3)
    return


main()