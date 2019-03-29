import itertools

import numpy as np


def normalize(X, axis=-1, order=2):
    """
    Normalize the data
    :param X: dataset
    :param axis: @see numpy.linalg.norm
    :param order: @see numpy.linalg.norm
    :return: normalized dataset
    """
    l2 = np.atleast_1d(np.linalg.norm(X, order, axis))
    l2[l2 == 0] = 1
    return X / np.expand_dims(l2, axis)


def polynomial_features(X, degree):
    """
    Polynomial the data
    :param X: dataset
    :param degree: number of features
    :return: new dataset
    """
    n_samples, n_features = np.shape(X)

    def index_combinations():
        combs = [itertools.combinations_with_replacement(range(n_features), i) for i in range(0, degree + 1)]
        flat_combs = [i for sublist in combs for i in sublist]
        return flat_combs

    combinations = index_combinations()
    n_output_features = len(combinations)
    X_new = np.empty((n_samples, n_output_features))

    for index, index_combs in enumerate(combinations):
        X_new[:, index] = np.prod(X[:, index_combs], axis=1)

    return X_new


def make_diagonal(x):
    """
    Get diagonal matrix of dataset
    """
    m = np.zeros((len(x), len(x)))
    for i in range(len(m[0])):
        m[i, i] = x[i]
    return m


def batch_iterator(X, y=None, batch_size=64):
    for i in np.arange(0, X.shape[0], batch_size):
        begin, end = i, min(i + batch_size, X.shape[0])
        if y is not None:
            yield X[begin: end], y[begin, end]
        else:
            yield X[begin: end]


def to_categorical(x, n_col=None):
    """
    One-hot encoding of nominal values
    :param x:
    :param n_col:
    :return:
    """
    if not n_col:
        n_col = np.amax(x) + 1

    one_hot = np.zeros((x.shape[0], n_col))
    one_hot[np.arange(x.shape[0]), x] = 1
    return one_hot


def shuffle_data(X, y, seed=None):
    """
    Random shuffle of the samples in X and y
    :param X: data sets
    :param y: label sets
    :param seed: random seed
    :return: shuffled data
    """
    if seed:
        np.random.seed(seed)
    idx = np.arange(X.shape[0])
    np.random.shuffle(idx)
    return X[idx], y[idx]


def accuracy_score(y_true, y_pred):
    """
    Compare y_true to y_pred and return the accuracy
    :param y_true:
    :param y_pred:
    :return:
    """
    return np.sum(y_true == y_pred, axis=0) / len(y_true)


def calculate_covariance_matrix(X, Y=None):
    """
    Calculate the covariance matrix for the dataset X
    :param X: dataset
    :param Y: dataset
    :return: covariance matrix
    """
    if not Y:
        Y = X
    n_samples = np.shape(X)[0]
    covariance_matrix = (1 / (n_samples -1)) * (X - X.mean(axis=0)).T.dot(Y - Y.mean(axis=0))
    return np.array(covariance_matrix, dtype=float)


def calculate_variance(X):
    """return the variance of the features in dataset X"""
    mean = np.ones(np.shape(X)) * X.mean(0)
    n_samples = np.shape(X)[0]
    variance = (1 / n_samples) * np.diag((X - mean).T.dot(X - mean))
    return variance


def calculate_std_dev(X):
    """Calculate the standard deviations of the features in dataset X"""
    return np.sqrt(calculate_variance(X))


def calculate_correlation_matrix(X, Y=None):
    """
    Calculate the correlation matrix for the dataset X
    :param X: dataset
    :param Y: dataset
    :return: covariance matrix
    """
    if not Y:
        Y = X
    n_samples = np.shape(X)[0]
    covariance = (1 / n_samples) * (X - X.mean(0)).T.dot(Y - Y.mean(0))
    std_dev_X = np.expand_dims(calculate_std_dev(X), 1)
    std_dev_y = np.expand_dims(calculate_std_dev(Y), 1)
    correlation_matrix = np.divide(covariance, std_dev_X.dot(std_dev_y.T))
    return np.array(correlation_matrix, dtype=float)
