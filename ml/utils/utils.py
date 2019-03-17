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
