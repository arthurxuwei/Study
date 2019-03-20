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


class RNN(Layer):
    """
    A vanilla Fully-Connected Recurrent Neural Network layer
    """

    def __init__(self, n_units, activation, bptt_trunc=5, input_shape=None):
        super(RNN, self).__init__()
        self.input_shape = input_shape
        self.n_units = n_units
        self.activation = activation
        self.trainable = True
        self.bptt_trunc = bptt_trunc
        self.W = None
        self.V = None
        self.U = None

    def initialize(self, optimizer):
        timesteps, input_dim = self.input_shape
        # init the weights
        limit = 1 / math.sqrt(input_dim)
        self.U = np.random.uniform(-limit, limit, (self.n_units, input_dim))
        limit = 1 / math.sqrt(self.n_units)
        self.V = np.random.uniform(-limit, limit, (input_dim, self.n_units))
        self.W = np.random.uniform(-limit, limit, (self.n_units, self.n_units))
        self.U_opt = copy.copy(optimizer)
        self.V_opt = copy.copy(optimizer)
        self.W_opt = copy.copy(optimizer)

    def parameters(self):
        return np.prod(self.W.shape) + np.prod(self.U.shape) + np.prod(self.V.shape)

    def forward_pass(self, X, training=True):
        self.layer_input = X
        batch_size, timesteps, input_dim = X.shape

        # Save these values for use in backprop.
        self.state_input = np.zeros((batch_size, timesteps, self.n_units))
        self.states = np.zeros((batch_size, timesteps + 1, self.n_units))
        self.outputs = np.zeros((batch_size, timesteps, input_dim))

        # Set last time step to zero for calculation of the state_input at time step zero
        self.states[:, -1] = np.zeros((batch_size, self.n_units))
        for t in range(timesteps):
            # input to state_t is the current input and output of previous states
            self.state_input[:, t] = X[:, t].dot(self.U.T) + self.states[:, t - 1].dot(self.W.T)
            self.states[:, t] = self.activation(self.state_input[:, t])
            self.outputs[: ,t] = self.states[:, t].dot(self.V.T)

        return self.outputs

    def backward_pass(self, accum_grad):
        _, timesteps, _ = accum_grad.shape

        # Variables where we save the accumulated gradient w.r.t each parameter
        grad_U = np.zeros_like(self.U)
        grad_V = np.zeros_like(self.V)
        grad_W = np.zeros_like(self.W)
        # The gradient w.r.t the layer input. Will be passed on to the previous layer in the network
        accum_grad_next = np.zeros_like(accum_grad)

        # Back Propagation Through Time
        for t in reversed(range(timesteps)):
            # Update gradient w.r.t V at time step t
            grad_v += accum_grad[:, t].T.dot(self.states[:, t])
            # Calculate the gradient w.r.t the state input
            grad_wrt_state = accum_grad[:, t].dot(self.V) * self.activation.gradient(self.state_input[:, t])
            # Gradient w.r.t the layer input
            accum_grad_next[:, t] = grad_wrt_state.dot(self.U)
            # Update gradient w.r.t W and U by backprop. from time step t for at most
            # self.bptt_trunc number of time steps
            for t_ in reversed(np.arange(max(0, t - self.bptt_trunc), t + 1)):
                grad_U += grad_wrt_state.T.dot(self.layer_input[:, t_])
                grad_W += grad_wrt_state.T.dot(self.states[:, t_ - 1])
                # Calculate gradient w.r.t previous state
                grad_wrt_state = grad_wrt_state.dot(self.W) * self.activation.gradient(self.state_input[:, t_ - 1])

        # Update weights
        self.U = self.U_opt.update(self.U, grad_U)
        self.V = self.V_opt.update(self.V, grad_V)
        self.W = self.W_opt.update(self.W, grad_W)

        return accum_grad_next

    def output_shape(self):
        return self.input_shape
