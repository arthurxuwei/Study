import numpy as np


class Loss(object):
    def loss(self, y, y_pred):
        pass

    def gradient(self, y, y_pred):
        pass

    def acc(self, y, y_pred):
        pass


class SquareLoss(Loss):
    def loss(self, y, y_pred):
        return 0.5 * np.power((y - y_pred), 2)

    def gradient(self, y, y_pred):
        return -(y - y_pred)


class CrossEntropy(Loss):
    def loss(self, y, y_pred):
        # Avoid division by zero
        y_pred = np.clip(y_pred, 1e-15, 1 - 1e-15)
        return - y * np.log(y_pred) - (1 - y) * np.log(1 - y_pred)

    def acc(self, y, y_pred):
        return np.sum(np.argmax(y, axis=1) == np.argmax(y_pred, axis=1), axis=0) / len(y)

    def gradient(self, y, y_pred):
        y_pred = np.clip(y_pred, 1e-15, 1 - 1e-15)
        return - (y / y_pred) + (1 - y) / (1 - y_pred)
