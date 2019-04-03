import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt

from deep.activations_functions import Sigmoid
from deep.loss_functions import CrossEntropy
from deep.perceptron import Perceptron
from utils.utils import accuracy_score


np.random.seed(0)
X, y = datasets.make_moons(200, noise=0.20)

clf = Perceptron(n_iterations=5000, learning_rate=0.001, loss=CrossEntropy, activation_function=Sigmoid)
clf.fit(X, y)


x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
h = 0.01
xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
tmp = np.c_[xx.ravel(), yy.ravel()]
Z = clf.predict(tmp)
y_pred = np.argmax(Z, axis=1)
accuracy = accuracy_score(y, y_pred)
print(f"Accuracy: {accuracy}")

plt.contourf(xx, yy, y_pred.reshape(xx.shape), cmap=plt.cm.get_cmap("Spectral"))
plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.get_cmap("Spectral"))
plt.show()
