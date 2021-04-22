import os
import matplotlib.pyplot as plt


files = ['graphInsert.txt', 'graphRemove.txt', 'graphSearch.txt']


def save(name='', fmt='png'):
    pwd = os.getcwd()
    iPath = '../pictures/'
    if not os.path.exists(iPath):
        os.mkdir(iPath)
    os.chdir(iPath)
    plt.savefig('{}.{}'.format(name, fmt), fmt='png')
    os.chdir(pwd)


for path in files:
    x = []
    y = []
    for line in open(os.path.join('..', 'calculations', path)):
        tmp = line.strip('\n').split()
        x.append(int(tmp[0]))
        y.append(float(tmp[1]))
    fig = plt.figure()

    ax = fig.add_subplot(111)

    ax.plot(x, y)
    ax.yaxis.set_label_position('left')
    ax.set_ylabel(u'Время, ns', rotation=90)

    ax.xaxis.set_label_position('bottom')
    ax.set_xlabel(u'Количество элементов графа')
    ax.set_title(path.replace(".txt", ""))
    ax.grid(True)
    save(path, fmt='png')
    '''plt.show()'''
