import numpy as np
from sklearn import datasets, linear_model
import matplotlib.pyplot as plt

from deep.activations_functions import Sigmoid
from deep.loss_functions import CrossEntropy
from deep.perceptron import Perceptron
from utils.utils import to_categorical


def plot_decision_boundary(pred_func):
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    tmp = np.c_[xx.ravel(), yy.ravel()]
    Z = pred_func(tmp)
    print(Z)
    Z = Z.reshape(xx.shape)

    plt.contourf(xx, yy, Z, cmap=plt.cm.get_cmap("Spectral"))
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.get_cmap("Spectral"))
    plt.show()


np.random.seed(0)
X, y = datasets.make_moons(200, noise=0.20)
plt.scatter(X[:, 0], X[:, 1], s=40, c=y, cmap=plt.cm.get_cmap("Spectral"))
plt.show()

clf = linear_model.LogisticRegression()
clf.fit(X, y)
plot_decision_boundary(clf.predict)

