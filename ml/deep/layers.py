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
            self.outputs[:, t] = self.states[:, t].dot(self.V.T)

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
            grad_V += accum_grad[:, t].T.dot(self.states[:, t])
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


class Conv2D(Layer):
    """
    2D Convolution Layer
    """
    def __init__(self, n_filters, filter_shape, input_shape=None, padding='same', stride=1):
        super(Conv2D, self).__init__()
        self.n_filters = n_filters
        self.filter_shape = filter_shape
        self.padding = padding
        self.stride = stride
        self.input_shape = input_shape
        self.trainable = True

    def initialize(self, optimizer):
        filter_height, filter_width = self.filter_shape
        channels = self.input_shape[0]
        limit = 1 / math.sqrt(np.prod(self.filter_shape))
        self.w = np.random.uniform(-limit, limit, size=(self.n_filters, channels, filter_height, filter_width))
        self.w0 = np.zeros((self.n_filters, 1))
        self.w_opt = copy.copy(optimizer)
        self.w0_opt = copy.copy(optimizer)

    def parameters(self):
        return np.prod(self.w.shape) + np.prod(self.w0.shape)

    def forward_pass(self, X, training=True):
        batch_size,  channels, height, width = X.shape
        self.layer_input = X
        # Turn image shape into column shape (enables dot product between input and weights)
        self.X_col = image_to_column(X, self.filter_shape, stride=self.stride, output_shape=self.padding)
        self.w_col = self.w.reshape((self.n_filters, -1))
        output = self.w_col.dot(self.X_col) + self.w0
        output = output.reshape(self.output_shape() + (batch_size,))
        return output.transpose(3, 0, 1, 2)

    def backward_pass(self, accum_grad):
        accum_grad = accum_grad.transpose(1, 2, 3, 0).reshape(self.n_filters, -1)
        if self.trainable:
            # Take dot product between column shaped accum. gradient and column shape
            # layer input to determine the gradient at the layer with respect to layer weights
            grad_w = accum_grad.dot(self.X_col.T).reshape(self.w.shape)
            # The gradient with respect to bias terms is the sum similarly to in Dense layer
            grad_w0 = np.sum(accum_grad, axis=1, keepdims=True)

            self.w = self.w_opt.update(self.w, grad_w)
            self.w0 = self.w0_opt.update(self.w0, grad_w0)

        # Recalculate the gradient which will be propogated back to prev. layer
        accum_grad = self.w_col.T.dot(accum_grad)
        # Reshape from column shape to image shape
        accum_grad = column_to_image(accum_grad, self.layer_input.shape, self.filter_shape, self.stride, self.padding)
        return accum_grad

    def output_shape(self):
        channels, height, width = self.input_shape
        pad_h, pad_w = determine_padding(self.filter_shape, output_shape=self.padding)
        output_height = (height + np.sum(pad_h) - self.filter_shape[0]) / self.stride + 1
        output_width = (width + np.sum(pad_w) - self.filter_shape[1]) / self.stride + 1
        return self.n_filters, int(output_height), int(output_width)


def determine_padding(filter_shape, output_shape="same"):
    """
    Method which calculates the padding based on the specified output shape and the shape of the filters
    """
    if output_shape == "valid":
        # no padding
        return (0, 0), (0, 0)
    elif output_shape == "same":
        # same shape between input and output
        filter_height, filter_width = filter_shape
        pad_h1 = int(math.floor((filter_height - 1)/2))
        pad_h2 = int(math.ceil((filter_height - 1)/2))
        pad_w1 = int(math.floor((filter_width - 1)/2))
        pad_w2 = int(math.ceil((filter_width - 1)/2))
        return (pad_h1, pad_h2), (pad_w1, pad_w2)


def image_to_column(images, filter_shape, stride, output_shape='same'):
    """
    Method which turns the image shaped input to column shape.
    """
    filter_height, filter_width = filter_shape
    pad_h, pad_w = determine_padding(filter_shape, output_shape)
    # Add padding
    images_padded = np.pad(images, ((0, 0), (0, 0), pad_h, pad_w), mode='constant')
    # Calculate the indices where the dot products are to be applied between weights and the image
    k, i, j = get_im2col_indices(images.shape, filter_shape, (pad_h, pad_w), stride)

    # Get content from image at those indices
    cols = images_padded[:, k, i, j]
    channels = images.shape[1]

    cols = cols.transpose(1, 2, 0).reshape(filter_height * filter_width * channels, -1)
    return cols


def column_to_image(cols, image_shapes, filter_shape, stride, output_shape='same'):
    """
    Method which turns the column shaped input to image shape
    """
    batch_size, channels, height, width = image_shapes
    pad_h, pad_w = determine_padding(filter_shape, output_shape)
    height_padded = height + np.sum(pad_h)
    width_padded = width + np.sum(pad_w)
    image_padded = np.empty((batch_size, channels, height_padded, width_padded))
    k, i, j = get_im2col_indices(image_shapes, filter_shape, (pad_h, pad_w), stride)

    cols = cols.reshape(channels * np.prod(filter_shape), -1, batch_size)
    cols = cols.transpose(2, 0, 1)
    # add column content to the images at the indices
    np.add.at(image_padded, (slice(None), k, i, j), cols)

    return image_padded[:, :, pad_h[0]:height + pad_h[0], pad_w[0]:width + pad_w[0]]


def get_im2col_indices(imags_shape, filter_shape, padding, stride=1):
    # First figure out what the size of the output should be
    batch_size, channels, height, width = imags_shape
    filter_height, filter_width = filter_shape
    pad_h, pad_w = padding
    out_height = int((height + np.sum(pad_h) - filter_height) / stride + 1)
    out_width = int((width + np.sum(pad_w) - filter_width) / stride + 1)
    i0 = np.repeat(np.arange(filter_height), filter_width)
    i0 = np.tile(i0, channels)
    i1 = stride * np.repeat(np.arange(out_height), out_width)
    j0 = np.tile(np.arange(filter_width), filter_height * channels)
    j1 = stride * np.tile(np.arange(out_width), out_height)
    i = i0.reshape(-1, 1) + i1.reshape(1, -1)
    j = j0.reshape(-1, 1) + j1.reshape(1, -1)
    k = np.repeat(np.arange(channels), filter_height * filter_width).reshape(-1, 1)
    return k, i, j


class BatchNormalization(Layer):
    """
    Batch normalization
    """
    def __init__(self, momentum=0.99):
        self.momentum = momentum
        self.trainable = True
        self.eps = 0.01
        self.running_mean = None
        self.running_var = None

    def initialize(self, optimizer):
        self.gamma = np.ones(self.input_shape)
        self.beta = np.zeros(self.input_shape)
        self.gamma_opt = copy.copy(optimizer)
        self.beta_opt = copy.copy(optimizer)

    def parameters(self):
        return np.prod(self.gamma.shape) + np.prod(self.beta.shape)

    def forward_pass(self, X, training=True):

        if self.running_mean is None:
            self.running_mean = np.mean(X, axis=0)
            self.running_var = np.var(X, axis=0)

        if training and self.trainable:
            mean = np.mean(X, axis=0)
            var = np.var(X, axis=0)
            self.running_mean = self.momentum * self.running_mean + (1 - self.momentum) * mean
            self.running_var = self.momentum * self.running_var + (1 - self.momentum) * var
        else:
            mean = self.running_mean
            var = self.running_var

        # statistics saved for backward pass
        self.X_centered = X - mean
        self.stddev_inv = 1 / np.sqrt(var + self.eps)

        X_norm = self.X_centered * self.stddev_inv
        output = self.gamma * X_norm + self.beta
        return output

    def backward_pass(self, accum_grad):
        gamma = self.gamma
        if self.trainable:
            X_norm = self.X_centered * self.stddev_inv
            grad_gamma = np.sum(accum_grad * X_norm, axis=0)
            grad_beta = np.sum(accum_grad, axis=0)

            self.gamma = self.gamma_opt.update(self.gamma, grad_gamma)
            self.beta = self.beta_opt.update(self.beta, grad_beta)

        batch_size = accum_grad.shape[0]
        # The gradient of the loss with respect to the layer inputs
        accum_grad = (1 / batch_size) * gamma * self.stddev_inv * (batch_size * accum_grad - np.sum(accum_grad, axis=0) - self.X_centered * self.stddev_inv**2 * np.sum(accum_grad * self.X_centered, axis=0))
        return accum_grad

    def output_shape(self):
        return self.input_shape


class PoolingLayer(Layer):
    """
    abstruct of pooling layer
    """
    def __init__(self, pool_shape=(2, 2), stride=1, padding=''):
        self.pool_shape = pool_shape
        self.stride = stride
        self.padding = padding
        self.trainable = True

    def forward_pass(self, X, training=True):
        self.layer_input = X
        batch_size, channels, height, width = X.shape
        _, out_height, out_width = self.output_shape()
        X = X.reshape(batch_size*channels, 1, height, width)
        X_col = image_to_column(X, self.pool_shape, self.stride, self.padding)
        output = self._pool_forward(X_col)
        output = output.reshape(out_height, out_width, batch_size, channels)
        output = output.transpose(2, 3, 0, 1)
        return output

    def backward_pass(self, accum_grad):
        batch_size, _, _, _ = accum_grad.shape
        channels, height, width = self.input_shape
        accum_grad = accum_grad.transpose(2, 3, 0, 1).ravel()

        accum_grad_col = self._pool_backward(accum_grad)
        accum_grad = column_to_image(accum_grad_col, (batch_size * channels, 1, height, width), self.pool_shape, self.stride, 0)
        accum_grad = accum_grad.reshape((batch_size,) + self.input_shape)
        return accum_grad

    def output_shape(self):
        channels, height, width = self.input_shape
        out_height = (height - self.pool_shape[0]) / self.stride + 1
        out_width = (width - self.pool_shape[1]) / self.stride + 1
        assert out_height % 1 == 0
        assert out_width % 1 == 0
        return channels, int(out_height), int(out_width)


class MaxPooling2D(PoolingLayer):
    def _pool_forward(self, X_col):
        arg_max = np.argmax(X_col, axis=0).flatten()
        output = X_col[arg_max, range(arg_max.size)]
        self.cache = arg_max
        return output

    def _pool_backward(self, accum_grad):
        accum_grad_col = np.zeros((np.prod(self.pool_shape), accum_grad.size))
        arg_max = self.cache
        accum_grad_col[arg_max, range(accum_grad.size)] = accum_grad
        return accum_grad_col


class AveragePooling2D(PoolingLayer):
    def _pool_forward(self, X_col):
        output = np.mean(X_col, axis=0)
        return output

    def _pool_backwar(self, accum_grad):
        accum_grad_col = np.zeros((np.prod(self.pool_shape), accum_grad.size))
        accum_grad_col[:, range(accum_grad.size)] = 1. / accum_grad_col.shape[0] * accum_grad
        return accum_grad_col


class ConstantPadding2D(Layer):
    """
    Adds rows and columns of constant values to the input.
     Expects the input to be of shape (batch_size, channels, height, width)
    """
    def __init__(self, padding, pading_value=0):
        self.padding = padding
        self.trainable = True
        if not isinstance(padding[0], tuple):
            self.padding = ((padding[0], padding[0]), padding[1])
        if not isinstance(padding[1], tuple):
            self.padding = (self.padding[0], (self.padding[1], padding[1]))
        self.padding_value = pading_value

    def forward_pass(self, X, traning=True):
        output = np.pad(X, pad_width=((0,0), (0,0), self.padding[0], self.padding[1]), mode="constant", constant_values=self.padding_value)
        return output

    def backward_pass(self, accum_grad):
        pad_top, pad_left = self.padding[0][0], self.padding[1][0]
        height, width = self.input_shape[1], self.input_shape[2]
        accum_grad = accum_grad[:, :, pad_top:pad_top+height, pad_left:pad_left+width]
        return accum_grad

    def output_shape(self):
        new_height = self.input_shape[1] + np.sum(self.padding[0])
        new_width = self.input_shape[2] + np.sum(self.padding[1])
        return self.input_shape[0], new_height, new_width


class ZeroPadding2D(ConstantPadding2D):
    """
    Adds rows and columns of zero values to the input
    """
    def __init__(self, padding):
        self.padding = padding
        if isinstance(padding[0], int):
            self.padding = ((padding[0], padding[0]), padding[1])
        if isinstance(padding[1], int):
            self.padding = (self.padding[0], (padding[1], padding[1]))
        self.padding = 0


class Flatten(Layer):
    """
    Turns a multidimensional matrix into two-dimensional
    """
    def __init__(self, input_shape=None):
        self.prev_shape = None
        self.trainable = True
        self.input_shape = input_shape

    def forward_pass(self, X, training=True):
        self.prev_shape = X.shape
        return X.reshape((X.shape[0], -1))

    def backward_pass(self, accum_grad):
        return accum_grad.reshape(self.prev_shape)

    def output_shape(self):
        return np.prod(self.input_shape),


class UpSampling2D(Layer):
    """
    Nearest neighbor up sampling of the input.
    Repeats the rows and columns of the data by size[0] and size[1] respectively.
    """
    def __init__(self, size=(2, 2), input_shape=None):
        self.prev_shape = None
        self.trainable = True
        self.size = size
        self.input_shape = input_shape

    def forward_pass(self, X, training=True):
        self.prev_shape = X.shape
        # Repeat each axis as specified by size
        X_new = X.repeat(self.size[0], axis=2).repeat(self.size[1], axis=3)
        return X_new

    def backward_pass(self, accum_grad):
        # Down sample input to previous shape
        accum_grad = accum_grad[:, :, ::self.size[0], ::self.size[1]]
        return accum_grad

    def output_shape(self):
        channels, height, width = self.input_shape
        return channels, self.size[0] * height,  self.size[1] * width


class Reshape(Layer):
    """
    Reshapes the input tensor into specified shape
    """
    def __init__(self, shape, input_shape=None):
        self.prev_shape = None
        self.trainable = True
        self.shape = shape
        self.input_shape = input_shape

    def forward_pass(self, X, training=True):
        self.prev_shape = X.shape
        return X.reshape((X.shape[0],) + self.shape)

    def backward_pass(self, accum_grad):
        return accum_grad.reshape(self.prev_shape)

    def output_shape(self):
        return self.shape



