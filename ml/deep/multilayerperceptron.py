import math
import numpy as np

from deep.activations_functions import Sigmoid, Softmax
from deep.loss_functions import CrossEntropy


class MultilayerPerceptron:
    """
    Multilayer Perceptron classifier.
    A fully-connected neural network with one hidden layer.
    """
    def __init__(self, n_hidden, n_iterations=3000, learning_rate=0.01):
        self.n_hidden = n_hidden
        self.n_iterations = n_iterations
        self.learning_rate = learning_rate
        self.hidden_activation = Sigmoid()
        self.output_activation = Softmax()
        self.loss = CrossEntropy()
        self.w = None
        self.w0 = None
        self.v = None
        self.v0 = None

    def fix(self, X, y):
        n_samples, n_features = X.shape
        _, n_outputs = y.shape

        # Hidden layer
        limit = 1 / math.sqrt(n_features)
        self.w = np.random.uniform(-limit, limit, (n_features, self.n_hidden))
        self.w0 = np.zeros((1, self.n_hidden))
        # Output layer
        limit = 1 / math.sqrt(self.n_hidden)
        self.v = np.random.uniform(-limit, limit, (self.n_hidden, n_outputs))
        self.v0 = np.zeros((1, n_outputs))

        for i in range(self.n_iterations):
            # forward pass
            # hidden layer
            hidden_input = X.dot(self.w) + self.w0
            hidden_output = self.hidden_activation(hidden_input)
            # output layer
            output_layer_input = hidden_output.dot(self.v) + self.v0
            y_pred = self.output_activation(output_layer_input)

            # backward pass
            # output layer
            grad_wrt_out_l_input = self.loss.gradient(y, y_pred) * self.output_activation.gradient(output_layer_input)
            grad_v = hidden_output.T.dot(grad_wrt_out_l_input)
            grad_v0 = np.sum(grad_wrt_out_l_input, axis=0, keepdims=True)
            # hidden layer
            grad_wrt_hidden_l_input = grad_wrt_out_l_input.dot(self.v.T) * self.hidden_activation.gradient(hidden_input)
            grad_w = X.T.dot(grad_wrt_hidden_l_input)
            grad_w0 = np.sum(grad_wrt_hidden_l_input, axis=0, keepdims=True)

            # Update weights (by gradient descent)
            # Move against the gradient to minimize loss
            self.v -= self.learning_rate * grad_v
            self.v0 -= self.learning_rate * grad_v0
            self.w -= self.learning_rate * grad_w
            self.w0 -= self.learning_rate * grad_w0

    def predict(self, X):
        hidden_input = X.dot(self.w) + self.w0
        hidden_output = self.hidden_activation(hidden_input)
        output_layer_input = hidden_output.dot(self.v) + self.v0
        y_pred = self.output_activation(output_layer_input)
        return y_pred
