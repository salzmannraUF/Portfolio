# Raymond Salzmann
# Machine Learning Homework 3
# December 13, 2020

import numpy as np
from matplotlib import pyplot as plt
from scipy.special import digamma,comb,betaln,gammaln


def read_csv():
    x = []
    with open(r'C:\Users\raymo\Desktop\ML\Homework3\data.csv') as file:
        lines = file.readlines()
        for line in lines:
            x.append(int(line.strip()))
        len_data = len(x)
        x = np.array(x).reshape([len_data,1])
    return x, len_data


def plot(x,l1,c1,l2,c2,l3,c3):
    plt.plot(range(1000), l1, label='K=3')
    plt.plot(range(1000), l2, label='K=15')
    plt.plot(range(1000), l3, label='K=50')
    plt.legend()
    plt.xlabel('Iterations')
    plt.ylabel('Log Likelihood')
    plt.title('Log Likelihood for varying Ks vs Iterations')
    plt.show()

    plt.scatter(x, c1)
    plt.title('K = 3')
    plt.show()

    plt.scatter(x, c2)
    plt.title('K = 15')
    plt.show()

    plt.scatter(x, c3)
    plt.title('K = 50')
    plt.show()
    return


def update_p(x,a,b,al,K,len_d):
    phi = np.zeros((len_d, K))
    for i in range(K):
        phi[:,i] = np.exp(x[:,0]*(digamma(a)[i]-digamma(a+b)[i])+(20-x[:,0])*(digamma(b)[i]-digamma(a+b)[i])+digamma(al)[i]-digamma(np.sum(al)))
    temp = np.sum(phi, axis=1)
    phi /= temp.reshape([len_d, 1])
    return phi


def update_qt(x,phi,a,b):
    a_prime = np.sum(phi*x,axis=0).reshape((len(a),1)) + a
    b_prime = np.sum(phi * (20-x), axis=0).reshape((len(a),1)) + b
    return a_prime,b_prime


def L1(x, ap, bp, alp, phi, K,len_d):
    csum = np.zeros((len_d, 1))
    for j in range(K):
        csum += phi[:, j].reshape((len_d, 1)) * ((np.log(comb(20, x))) + x * (digamma(ap) - (digamma(ap + bp)))[j] + (20 - x) * (digamma(bp) - (digamma(ap + bp)))[j] + (digamma(alp) - digamma(np.sum(alp)))[j])
    return np.sum(csum)


def L3(al, alp, K):
    part1 = sum(map(lambda i: gammaln(al[i]), range(K)))
    part2 = sum(map(lambda i : (al[i] - 1) * digamma(alp[i]), range(K)))
    return (part1 - gammaln(sum(al)) - (K - sum(al)) * digamma(np.sum(alp)) - part2)[0]


def L4(al, K):
    part1 = sum(map(lambda i: gammaln(al[i]),range(K)))
    part2 = sum(map(lambda i: (al[i]-1)*digamma(al[i]),range(K)))
    return (part1-gammaln(sum(al))-(K-sum(al))*digamma(sum(al))-part2)[0]


def VI(x,len_d,K):
    a = np.ones((K, 1)) * 0.5
    b = np.ones((K, 1)) * 0.5
    al = np.random.rand(K,1).reshape((K,1))

    clus = []
    elbo = []

    phi = update_p(x, a, b, al, K, len_d)
    for i in range(1000):
        nj = np.sum(phi,axis=0)
        alp = al + nj.reshape((len(nj), 1))
        ap, bp = update_qt(x, phi, a, b)

        elbo1 = L1(x, ap, bp, alp, phi, K, len_d)

        elbo2 = np.sum((a - 1) * (digamma(ap) - digamma(ap + bp)) + (b - 1) * (digamma(bp) - digamma(ap + bp)) - betaln(a, b))

        elbo3 = L3(al, alp, K)

        elbo4 = L4(alp, K)

        elbo5 = np.sum((ap - 1) * (digamma(ap) - digamma(ap + bp)) + (bp - 1) * (digamma(bp) - digamma(ap + bp)) - betaln(ap, bp))

        elbo6 = np.sum(phi * np.log(phi))

        phi = update_p(x, ap, bp, alp, K, len_d)
        elbo.append(elbo1 + elbo2 - elbo3 + elbo4 - elbo5 - elbo6)

    for j in range(len_d):
        clus.append(np.argmax(phi[j, :]))
    return elbo, clus


def main():
    x, len_data = read_csv()

    l1,c1 = VI(x, len_data, 3)
    l2,c2 = VI(x, len_data, 15)
    l3,c3 = VI(x, len_data, 50)

    plot(x,l1,c1,l2,c2,l3,c3)
    return


main()
