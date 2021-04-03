import os
import matplotlib.pyplot as plt


files = ['InsertionSort.txt', 'QuickSort.txt']


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
    ax.set_ylabel(u'Время, ms', rotation=90)

    ax.xaxis.set_label_position('bottom')
    ax.set_xlabel(u'Количество элементов массива')
    ax.set_title(path)
    ax.grid(True)
    save(path, fmt='png')
    '''plt.show()'''

x1 = []
y1 = []
x2 = []
y2 = []
for line in open(os.path.join('..', 'calculations', 'InsertionSort.txt')):
    tmp = line.strip('\n').split()
    x1.append(float(tmp[0]))
    y1.append(float(tmp[1]))

for line in open(os.path.join('..', 'calculations', 'QuickSort.txt')):
    tmp = line.strip('\n').split()
    x2.append(float(tmp[0]))
    y2.append(float(tmp[1]))
fig = plt.figure()

ax = fig.add_subplot(111)

ax.plot(x1, y1, x2, y2)
ax.yaxis.set_label_position('left')
ax.set_ylabel(u'Время, ns', rotation=90)

ax.xaxis.set_label_position('bottom')
ax.set_xlabel(u'Количество элементов массива')
ax.set_title('QuickSort and InsertionSort')
ax.grid(True)
save('QuickSort and InsertionSort', fmt='png')
