import numpy as np


class NeuralNetwork:
    def __init__(self, layers, activation, activation_deriv):
        """
        :param layers: A list containing the number of units in each layer. Should be at least two values
        :param activation: The activation function to be used. Can be "logistic" or "tanh"
        """
        self.activation = activation
        self.activation_deriv = activation_deriv

        self.weights = []
        for i in range(1, len(layers) - 1):
            self.weights.append((2 * np.random.random((layers[i - 1] + 1, layers[i] + 1)) - 1) * 0.25)
            self.weights.append((2 * np.random.random((layers[i] + 1, layers[i + 1])) - 1) * 0.25)

    def fit(self, mX, y, learning_rate=0.2, epochs=1000):
        """
        :param mX: matrix of instance
        :param y: label
        :param learning_rate: learning_rate
        :param epochs: iterator times
        """
        mX = np.atleast_2d(mX)
        temp = np.ones([mX.shape[0], mX.shape[1] + 1])
        temp[:, 0:-1] = mX
        mX = temp
        y = np.array(y)

        for k in range(epochs):
            i = np.random.randint(mX.shape[0])
            a = [mX[i]]

            for l in range(len(self.weights)):
                a.append(self.activation(np.dot(a[l], self.weights[l])))

            error = y[i] - a[-1]
            deltas = [error * self.activation_deriv(a[-1])]

            for l in range(len(a) - 2, 0, -1):
                deltas.append(deltas[-1].dot(self.weights[l].T) * self.activation_deriv(a[l]))

            deltas.reverse()

            for i in range(len(self.weights)):
                layer = np.atleast_2d(a[i])
                delta = np.atleast_2d(deltas[i])
                self.weights[i] += learning_rate * layer.T.dot(delta)
                

    def predict(self, mX):
        """
        :param mX:
        :return: predict result
        """
        predictions = []
        for i in range(mX.shape[0]):
            temp = np.ones(mX[i].shape[0] + 1)
            temp[0:-1] = mX[i]
            for l in range(0, len(self.weights)):
                temp = self.activation(np.dot(temp, self.weights[l]))
            predictions.append(np.argmax(temp))
        return np.array(predictions)


