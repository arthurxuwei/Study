import copy
import math
import numpy as np


class Layer(object):
    def __init__(self):
        self.input_shape = None

    def set_input_shape(self, shape):
        """
        Sets the shape that the layer expects of the input in the forward pass method
        """
        self.input_shape = shape

    def layer_name(self):
        """
        The name of the layer. Used in model summary.
        """
        return self.__class__.__name__

    def parameters(self):
        """
        The number of trainable parameters used by the layer
        """
        pass

    def forward_pass(self, X, training=True):
        """
        Propogates the signal forward in the network
        """
        pass

    def backward_pass(self, accum_grad):
        """
        Propogates the accumulated gradient backwards.
        If the has trainable weights then these weights are also tuned in this method.
        :param accum_grad: receives the gradient with respect to the output of the layer
        :return the gradient with respect to the output of the previous layer
        """
        pass

    def output_shape(self):
        """
        The shape of the output produced by forward_pass
        """
        pass


class Dense(Layer):
    """A fully-connected NN layer"""
    def __init__(self, n_units, input_shape=None):
        super(Dense, self).__init__()
        self.layer_input = None
        self.input_shape = input_shape
        self.n_units = n_units
        self.trainable = True
        self.w = None
        self.w0 = None
        self.w_opt = None
        self.w0_opt = None

    def initialize(self, optimizer):
        # init the weights
        limit = 1 / math.sqrt(self.input_shape[0])
        self.w = np.random.uniform(-limit, limit, (self.input_shape[0], self.n_units))
        self.w0 = np.zeros(1, self.n_units)

        self.w_opt = copy.copy(optimizer)
        self.w0_opt = copy.copy(optimizer)

    def parameters(self):
        return np.prod(self.w.shape) + np.prod(self.w0.shape)

    def forward_pass(self, X, training=True):
        self.layer_input = X
        return X.dot(self.w) + self.w0

    def backward_pass(self, accum_grad):
        w = self.w
        if self.trainable:
            grad_w = self.layer_input.T.dot(accum_grad)
            grad_w0 = np.sum(accum_grad, axis=0, keepdims=True)

            self.w = self.w_opt.update(self.w, grad_w)
            self.w0 = self.w0_opt.update(self.w0, grad_w0)

        accum_grad = accum_grad.dot(w.T)
        return accum_grad

    def output_shape(self):
        return self.n_units,
