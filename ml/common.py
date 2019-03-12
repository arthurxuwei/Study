import numpy as np


def tanh(x):
    return np.tanh(x)


def tanh_deriv(x):
    return 1.0 - np.tanh(x)**2


def logistic(x):
    return 1/(1 + np.exp(-x))


def logistic_derivative(x):
    return logistic(x)*(1-logistic(x))

def relu(x):
    return np.maximum(z, 0.0)

def relu(x):
<<<<<<< HEAD
    return np.where(z <= 0, 0, 1)
=======
    return np.where(z <= 0, 0, 1)
>>>>>>> cfa736387e092630fa592e42074396eb4fc6a089
