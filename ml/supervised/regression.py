import math
import numpy as np


class Regression(object):
    """
        Base regression model.
    """
    def __init__(self, n_iterations: int, learning_rate: float):
        """
        :param n_iterations: training iterations
        :param learning_rate: the step length that will be used when updating the weights
        """
        self.training_errors = []
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate
        self.w = np.array((0, 0))
        self.regularization = lambda x: x

    def initialize_weights(self, n_features: int):
        """
        Init weights
        :param n_features: number of feature
        """
        limit = 1 / math.sqrt(n_features)
        self.w = np.random.uniform(-limit, limit, (n_features,))

    def fit(self, X, y):
        # insert constant ones for bias weights
        X = np.insert(X, 0, 1, axis=1)
        self.initialize_weights(X.shape[1])

        # Do gradient descent for n_iterations
        for i in range(self.n_iterations):
            y_pred = X.dot(self.w)

            mse = np.mean(0.5 * (y - y_pred)**2 + self.regularization(self.w))
            self.training_errors.append(mse)

            grad_w = -(y - y_pred).dot(X) + self.regularization.grad(self.w)
            self.w -= self.learning_rate * grad_w

    def predict(self, X):
        X = np.insert(X, 0, 1, axis=1)
        return X.dot(self.w)
