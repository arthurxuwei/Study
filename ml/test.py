import numpy as np
from scipy import ndimage
from sklearn import linear_model, datasets, metrics, model_selection, neural_network, pipeline

digits = datasets.load_digits()
direction_vectors = [
        [[0, 1, 0],
         [0, 0, 0],
         [0, 0, 0]],

        [[0, 0, 0],
         [1, 0, 0],
         [0, 0, 0]],

        [[0, 0, 0],
         [0, 0, 1],
         [0, 0, 0]],

        [[0, 0, 0],
         [0, 0, 0],
         [0, 1, 0]]
]

X = digits.data
Y = digits.target

print(f"digits.data: {X}, dim: {X.shape}")
shift = lambda x, w: ndimage.convolve(x.reshape((8,8)), mode='constant', weights=w).ravel()
print(f"X[0]: {np.apply_along_axis(shift, 1, X, direction_vectors[0])}")
X = np.concatenate([X] + [np.apply_along_axis(shift, 1, X, vector) for vector in direction_vectors])
print(f"X: {X}, dim: {X.shape}")
X = (X - np.min(X, 0)) /(np.max(X, 0) + 0.0001)
print(f"X: {X}, dim: {X.shape}")

print(f"digits.target: {Y}, dim: {Y.shape}")
Y = np.concatenate([Y for _ in range(5)], axis = 0)
print(f"Y: {Y}, dim: {Y.shape}")
