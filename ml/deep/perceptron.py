import math

import numpy as np
from deep.activations_functions import Sigmoid
from deep.loss_functions import SquareLoss


class Perceptron:
    """
    The Perceptron. One layer neural network classifier
    """
    def __init__(self, n_iterations=20000, learning_rate=0.01, activation_function=Sigmoid, loss=SquareLoss):
        """
        :param n_iterations:  the number of training iterations
        :param learning_rate:  the step length
        :param activation_function: the activation( Sigmoid, ExpLU, ReLU, LeakyReLU, SoftPlus, TanH )
        :param loss: assess the model's performance ( SquareLoss, CrossEntropy )
        """
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate
        self.loss = loss()
        self.activation_function = activation_function()
        self.w = None
        self.w0 = None

    def fit(self, X, y):
        n_samples, n_features = np.shape(X)
        if len(np.shape(y)) == 1:
            n_outputs = np.shape(y)[0]
        else:
            _, n_outputs = np.shape(y)

        # Initialize weights between [-1/sqrt(N), 1/sqrt(N)]
        limit = 1 / math.sqrt(n_features)
        self.w = np.random.uniform(-limit, limit, (n_features, n_outputs))
        self.w0 = np.zeros((1, n_outputs))

        for i in range(self.n_iterations):
            linear_output = X.dot(self.w) + self.w0
            y_pred = self.activation_function(linear_output)
            # Calculate the loss gradient w.r.t the input of the activation function
            error_gradient = self.loss.gradient(y, y_pred) * self.activation_function.gradient(linear_output)
            # Calculate the gradient of the loss with respect to each weight
            grad_wrt_w = X.T.dot(error_gradient)
            grad_wrt_w0 = np.sum(error_gradient, axis=0, keepdims=True)

            self.w -= self.learning_rate * grad_wrt_w
            self.w0 -= self.learning_rate * grad_wrt_w0

    def predict(self, X):
        return self.activation_function(X.dot(self.w) + self.w0)
