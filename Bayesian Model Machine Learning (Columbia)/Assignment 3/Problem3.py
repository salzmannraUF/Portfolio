# Raymond Salzmann
# Machine Learning Homework 3
# December 13, 2020

import matplotlib.pyplot as plt
import numpy as np
import random
from scipy.stats import binom
from scipy.special import beta, comb

def read_csv():
    x = []
    with open(r'C:\Users\raymo\Desktop\ML\Homework3\data.csv') as file:
        lines = file.readlines()
        for line in lines:
            x.append(int(line.strip()))
        len_data = len(x)
        x = np.array(x).reshape([len_data, 1])
    return x, len_data


def init(x,al,a,b,len_d):
    pp = []
    for i in range(len_d):
        pp.append((al/(al+len_d-1))*(comb(20,x))*(beta(a+x,b+20-x)/beta(a,b)))

    cl = dict()
    t = dict()
    for i in range(30):
        cl[i] = []
        t[i] = np.random.beta(a, b)

    c = []
    for i in range(len_d):
        idx = random.randint(0, 29)
        c.append(idx)
        cl[idx].append(i)

    return cl,t,c,pp


def plot(cnum,max_c):
    plt.plot(range(1000), cnum)
    plt.xlabel('Iterations')
    plt.ylabel('Number of Clusters')
    plt.title('Number of Clusters vs Iterations')
    plt.show()

    for i in max_c:
        plt.plot(range(1000), max_c[i], label=str(i) + 'th Largest')
    plt.legend()
    plt.xlabel('Iterations')
    plt.ylabel('Points in Cluster')
    plt.title('Points in Cluster vs Iterations')
    plt.show()


def Gibbs(x,al,a,b,len_d):
    cl,t,c,pp = init(x,al,a,b,len_d)

    max_c = {0: [], 1: [], 2: [], 3: [], 4: [], 5: []}
    cnum = []

    for iter in range(1000):
        len_c = [len(cl[i]) for i in cl]
        len_c.sort(reverse=True)

        if len(cl) < 6:
            for i in range(len(cl)):
                max_c[i].append(len_c[i])
            for i in range(len(cl), 6):
                max_c[i].append(0)
        else:
            for i in range(6):
                max_c[i].append(len_c[i])
        cnum.append(len(cl))

        for i in range(len_d):
            check = 0
            p = []

            for w in cl:
                if c[i] == w:
                    cl[w].remove(i)
                p.append(binom.pmf(x[i,0],20,t[w])*len(cl[w])/(al+len_d-1))

            p.append(pp[i])
            p = np.array(p)
            p /= np.sum(p)
            c[i] = int(np.random.choice(len(p), 1, p=p))

            try:
                cl[c[i]].append(i)
            except KeyError:
                cl[c[i]] = [i]
                
            if c[i] == len(p) - 1:
                t[c[i]] = beta(a + x[i, 0], b + 2 - x[i, 0])

            for key in list(cl):
                if len(cl[key]) == 0:
                    check = 1
                    del cl[key]

            if check == 1:
                lk = list(cl.keys())
                tn = {}
                for j in range(len(lk)):
                    tn[j] = t[lk[j]]
                t = tn
                c_new = []
                cl.clear
                for m in range(len_d):
                    for j in range(len(lk)):
                        if c[m] == lk[j]:
                            c_new.append(j)
                            try:
                                cl[j].append(m)
                            except KeyError:
                                cl[j] = [m]
                c = c_new
                print((1000-iter) + 's left to go!')

            for w in cl:
                t[w] = np.random.beta(a + np.sum(x[cl[w], :]), b + np.sum(20 - x[cl[w], :]))
        return cnum, max_c

def main():
    al = 3/4
    a = 1/2
    b = 1/2

    x,len_data = read_csv()
    cnum,max_c = Gibbs(x,al,a,b,len_data)
    plot(cnum, max_c)
    return

main()