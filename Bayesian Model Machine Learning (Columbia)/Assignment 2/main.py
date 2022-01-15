# Raymond Salzmann
# Machine Learning Homework 2
# Due: November 1, 2020

import pandas as pd
import numpy as np
from scipy.special import digamma, gammaln
import matplotlib.pyplot as plt


def read_csv():
    data_1_x = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\X_set1.csv')
    data_1_y = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\y_set1.csv')
    data_1_z = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\z_set1.csv')
    data_2_x = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\X_set2.csv')
    data_2_y = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\y_set2.csv')
    data_2_z = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\z_set2.csv')
    data_3_x = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\X_set3.csv')
    data_3_y = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\y_set3.csv')
    data_3_z = pd.read_csv(r'C:\Users\raymo\Desktop\ML\Homework2\z_set3.csv')
    return data_1_x, data_1_y, data_1_z, data_2_x, data_2_y, data_2_z, data_3_x, data_3_y, data_3_z


def update_ql(e, f, mu, sigma, n, yty, ytxt, xxt):
    return (0.5 * n + e), (0.5 * (yty - 2 * np.dot(ytxt, mu) + np.trace(np.dot(sigma + np.dot(mu, mu.T), xxt))) + f)


def update_qak(a, b, mu, sigma, k):
    return (0.5 + a), (0.5 * (pow(mu[k], 2) + sigma[k, k]) + b)


def update_qw(a, b, e, f, xxt, x, y):
    return (e / f) * np.dot(np.dot(np.linalg.inv((e / f) * xxt + np.diag(a / b)), x.T), y), (np.linalg.inv((e / f) * xxt + np.diag(a / b)))


def VI(x, y, iterations, dim, n):
    a_0 = b_0 = 10e-16
    e_0 = f_0 = 1
    a = np.array([a_0] * dim)
    b = np.array([b_0] * dim)
    e = e_0
    f = f_0
    mu = np.zeros(dim)
    sigma = np.diag(np.ones(dim))
    ELBO = []

    for t in range(iterations):
        e, f = update_ql(e_0, f_0, mu, sigma, n, np.dot(y.T, y)[0][0], np.dot(y.T, x), np.dot(x.T, x))
        ap = []
        bp = []

        for k in range(dim):
            ak, bk = update_qak(a_0, b_0, mu, sigma, k)
            ap.append(ak); bp.append(bk)
        a = np.array(ap)
        b = np.array(bp)
        b = b.flatten()
        mu, sigma = update_qw(a, b, e, f, np.dot(x.T, x), x, y)

        # L1
        L1 = - 0.5 * dim * np.log(2 * np.pi) + 0.5 * sum(map(lambda adb: digamma(adb[0]) - np.log(adb[1]), zip(a, b))) - 0.5 * np.trace(np.dot(sigma + np.dot(mu, mu.T), np.diag(a/b)))

        # L2
        L2 = e_0 * np.log(f_0) - gammaln(e_0) + (e_0 -1) * (digamma(e) - np.log(f)) - f_0 * (e/f)

        # L3
        L3 = sum(map(lambda adb: a_0 * np.log(b_0) - gammaln(a_0) + (a_0-1) * (digamma(adb[0]) - np.log(adb[1])) - (b_0 * adb[0]/adb[1]), zip(a, b)))

        # L4
        sign, logdet = np.linalg.slogdet(sigma)
        L4 = -0.5*(sign * logdet)

        # L5
        L5 = np.log(f) - gammaln(e) + (e - 1) * digamma(e) - e

        # L6
        L6 = sum(map(lambda adb: np.log(adb[1]) - gammaln(adb[0]) + (adb[0] - 1) * digamma(adb[0]) - adb[0], zip(a, b)))

        # L7
        L7 = 0.5 * n * (digamma(e) - np.log(f) - np.log(2 * np.pi)) - 0.5 * (e/f) * (np.dot(y.T, y)[0][0] - 2 * np.dot(np.dot(y.T, x), mu) + np.trace(np.dot((np.dot(mu, mu.T) + sigma), np.dot(x.T, x))))

        ELBO.append((L1 + L2 + L3 + L4 + L5 + L6 + L7)[0][0])

    return a, b, e, f, mu, ELBO


def plot_stuff(a, b, e, f, mu, dim, ELBO, xdata, ydata, zdata, setno):
    # Part A
    plt.plot(range(500), ELBO)
    plt.xlabel('Iterations')
    plt.ylabel('Variational Objective Function Value')
    plt.title('Variational Objective Function vs Iterations for Set ' + str(setno))

    # Part B
    plt.plot(range(dim), (1 / (a/b)))
    plt.xlabel('K')
    plt.ylabel('1 / Expectation(q[alpha_k])')
    plt.title('1 / Expectation(q[alpha_k]) vs K for Set ' + str(setno))

    # Part C
    print('1/E_q[lambda] for Set ' + str(setno) + ' = ', (f/e))

    # Part D
    y_hat = np.dot(xdata, mu)
    plt.plot(zdata, y_hat, 'r', label='Y_hat')
    plt.plot(zdata, 10 * np.sinc(zdata), 'b', label='Ground Truth')
    plt.scatter(zdata, ydata, s=8, c='black', label='(Zi, Yi)')
    plt.xlabel('Zi')
    plt.ylabel('Yi')
    plt.legend()
    plt.title('Y_hat, Ground Truth, and (Zi,Yi) Scatter for Set ' + str(setno))


def main():
    # Get all the data
    data_1_x, data_1_y, data_1_z, data_2_x, data_2_y, data_2_z, data_3_x, data_3_y, data_3_z = read_csv()
    dim1 = data_1_x.shape[1]
    n1 = data_1_x.shape[0]
    dim2 = data_2_x.shape[1]
    n2 = data_2_x.shape[0]
    dim3 = data_3_x.shape[1]
    n3 = data_3_x.shape[0]

    # Calculate all of the needed parameters
    a_1, b_1, e_1, f_1, mu_1, ELBO_1 = VI(data_1_x, data_1_y, 500, dim1, n1)
    a_2, b_2, e_2, f_2, mu_2, ELBO_2 = VI(data_2_x, data_2_y, 500, dim2, n2)
    a_3, b_3, e_3, f_3, mu_3, ELBO_3 = VI(data_3_x, data_3_y, 500, dim3, n3)

    # plot things
    plot_stuff(a_1, b_1, e_1, f_1, mu_1, dim1, ELBO_1, data_1_x, data_1_y, data_1_z, 1)
    plot_stuff(a_2, b_2, e_2, f_2, mu_2, dim2, ELBO_2, data_2_x, data_2_y, data_2_z, 2)
    plot_stuff(a_3, b_3, e_3, f_3, mu_3, dim3, ELBO_3, data_3_x, data_3_y, data_3_z, 3)
    return

main()