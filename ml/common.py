import numpy as np


def tanh(x):
    return np.tanh(x)


def tanh_deriv(x):
    return 1.0 - np.tanh(x)**2


def logistic(x):
    return 1/(1 + np.exp(-x))


def logistic_deriv(x):
    return logistic(x)*(1-logistic(x))


def relu(x):
    return np.maximum(x, 0.0)


def relu_deriv(x):
    return np.where(x <= 0, 0, 1)

