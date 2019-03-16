import math
from typing import Callable

import numpy as np

from utils.utils import normalize, polynomial_features


class Regularization:
    """
    Empty Regularization
    """
    def __init__(self, alpha):
        self.alpha = alpha

    def __call__(self, w):
        return self.alpha * w

    def grad(self, w):
        return self.alpha * w


class L1Regularization(Regularization):
    """
    L1 Regularization
    """
    def __init__(self, alpha):
        super(L1Regularization, self).__init__(alpha=alpha)

    def __call__(self, w):
        return self.alpha * np.linalg.norm(w)

    def grad(self, w):
        return self.alpha * np.sign(w)


class L2Regularization(Regularization):
    """
    L2 Regularization
    """
    def __init__(self, alpha):
        super(L2Regularization, self).__init__(alpha=alpha)

    def __call__(self, w):
        return self.alpha * 0.5 * w.T.dot(w)

    def grad(self, w):
        return self.alpha * w


class L1L2Regularization(Regularization):
    """
    L1L2 Regularization
    """
    def __init__(self, alpha, l1_ratio=0.5):
        super(L1L2Regularization, self).__init__(alpha=alpha)
        self.l1_ratio = l1_ratio

    def __call__(self, w):
        l1_contr = self.l1_ratio * np.linalg.norm(w)
        l2_contr = (1 - self.l1_ratio) * 0.5 * w.T.dot(w)
        return self.alpha * (l1_contr + l2_contr)

    def grad(self, w):
        l1_contr = self.l1_ratio * np.sign(w)
        l2_contr = (1 - self.l1_ratio) * w
        return self.alpha * (l1_contr + l2_contr)


class Regression(object):
    """
        Regression interface
    """
    def __init__(self, n_iterations: int, learning_rate: float):
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate

    def fit(self, X, y):
        pass

    def predict(self, X):
        pass


class GDLinearRegression(Regression):
    """
        Linear model with gradient descent.
    """
    def __init__(self, n_iterations: int, learning_rate: float, regularization: Regularization = Regularization(0)):
        super(GDLinearRegression, self).__init__(n_iterations, learning_rate)
        self.regularization = regularization
        self.training_errors = []
        self.w = np.array((0, 0))

    def fit(self, X, y):
        # insert constant ones for bias weights
        X = np.insert(X, 0, 1, axis=1)
        # init weights
        limit = 1 / math.sqrt(X.shape[1])
        self.w = np.random.uniform(-limit, limit, (X.shape[1],))

        # Do gradient descent
        for i in range(self.n_iterations):
            y_pred = X.dot(self.w)

            mse = np.mean(0.5 * (y - y_pred)**2 + self.regularization(self.w))
            self.training_errors.append(mse)

            grad_w = -(y - y_pred).dot(X) + self.regularization.grad(self.w)
            self.w -= self.learning_rate * grad_w

    def predict(self, X):
        X = np.insert(X, 0, 1, axis=1)
        return X.dot(self.w)


class SVDLinearRegression(Regression):
    """
        Linear model with SVD.
    """
    def __init__(self, n_iterations: int = 100,  learning_rate: float = 0.001):
        super(SVDLinearRegression, self).__init__(n_iterations, learning_rate)
        self.w = np.array(0, 0)

    def fit(self, X, y):
        # insert constant ones for bias weights
        X = np.insert(X, 0, 1, axis=1)
        # Do SVD
        U, S, V = np.linalg.svd(X.T.dot(X))
        S = np.diag(S)
        X_sq_reg_inv = V.dot(np.linalg.pinv(S)).dot(U.T)
        self.w = X_sq_reg_inv.dot(X.T).dot(y)

    def predict(self, X):
        X = np.insert(X, 0, 1, axis=1)
        return X.dot(self.w)


class PolynomialRegression(GDLinearRegression):
    """
        Performs a non-linear transformation of the data before fitting and predictions
        Allows for non-linear regression
    """
    def __init__(self, degree, n_iterations=3000, learning_rate=0.01):
        """
        :param degree: the degree of the polynomial
        """
        super(PolynomialRegression, self).__init__(n_iterations, learning_rate)
        self.degree = degree

    def fit(self, X, y):
        X = polynomial_features(X, degree=self.degree)
        super(PolynomialRegression, self).fit(X, y)

    def predict(self, X):
        X = polynomial_features(X, degree=self.degree)
        return super(PolynomialRegression, self).predict(X)


class RidgeRegression(GDLinearRegression):
    """
    Linear regression model with a regularization factor.Model that
    tries to balance the fit of the model with respect to the training data and the complexity of the model.
    A large regularization factor with decreases the variance of the model and do para
    """
    def __init__(self, reg_factor, n_iterations=1000, learning_rate=0.001):
        """
        :param reg_factor: the factor that determine the amount of regularization and feature
        """
        super(RidgeRegression, self).__init__(n_iterations, learning_rate, L2Regularization(reg_factor))


class LassoRegression(GDLinearRegression):
    """
        Linear model with a regularization factor which does both variable selection and regularization.
    """
    def __init__(self, degree, reg_factor, n_iterations=3000, learning_rate=0.01):
        super(LassoRegression, self).__init__(n_iterations, learning_rate, L1Regularization(reg_factor))
        self.degree = degree

    def fit(self, X, y):
        X = normalize(polynomial_features(X, degree=self.degree))
        super(LassoRegression, self).fit(X, y)

    def predict(self, X):
        X = normalize(polynomial_features(X, degree=self.degree))
        return super(LassoRegression, self).predict(X)


class PolynomialRidgeRegression(GDLinearRegression):
    """
    Similar to regular ridge regression except that the data is transformed to allow for polynomial regression.
    """
    def __init__(self, degree, reg_factor, n_iterations=3000, learning_rate=0.01):
        super(PolynomialRidgeRegression, self).__init__(n_iterations, learning_rate, L2Regularization(reg_factor))
        self.degree = degree

    def fit(self, X, y):
        X = normalize(polynomial_features(X, degree=self.degree))
        super(PolynomialRidgeRegression, self).fit(X, y)

    def predict(self, X):
        X = normalize(polynomial_features(X, degree=self.degree))
        super(PolynomialRidgeRegression, self).predict(X)


class ElasticNet(GDLinearRegression):
    """
    Regression where a combination of L1 and L2 regularization are used
    """
    def __init__(self, degree=1, reg_factor=0.05, l1_ratio=0.5, n_iterations=3000, learning_rate=0.01):
        """
        :param l1_ratio: Weighs the contribution of l1 and l2 regularization.
        """
        super(ElasticNet, self).__init__(n_iterations, learning_rate, L1L2Regularization(reg_factor, l1_ratio=l1_ratio))
        self.degree = degree

    def fit(self, X, y):
        X = normalize(polynomial_features(X, degree=self.degree))
        super(ElasticNet, self).fit(X, y)

    def predict(self, X):
        X = normalize(polynomial_features(X, degree=self.degree))
        super(ElasticNet, self).predict(X)
