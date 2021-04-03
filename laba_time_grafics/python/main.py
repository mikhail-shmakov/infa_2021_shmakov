import os
import matplotlib.pyplot as plt


files = ['vec.push_back.txt', 'lst.push_back.txt', 'vec.pop_back.txt', 'lst.pop_back.txt', 'vec.push_front.txt',
         'lst.push_front.txt']
'''files = ['lst.pop_back_test.txt']'''


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
        x.append(float(tmp[0]))
        y.append(float(tmp[1]))
    fig = plt.figure()

    ax = fig.add_subplot(111)

    ax.plot(x, y)
    ax.yaxis.set_label_position('left')
    ax.set_ylabel(u'Время, ns', rotation=90)

    ax.xaxis.set_label_position('bottom')
    ax.set_xlabel(u'Количество элементов массива')
    ax.set_title(path)
    ax.grid(True)
    save(path, fmt='png')


