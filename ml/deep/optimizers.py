import numpy as np

# optimizers for models that use gradient based methods for finding the weights that minimized the loss
# http://sebastianruder.com/optimizing-gradient-descent/index.html


class StochasticGradientDescent:
    def __init__(self, learning_rate=0.01, momentum=0):
        self.learning_rate = learning_rate
        self.momentum = momentum
        self.w_updt = None

    def update(self, w, grad_wrt_w):
        if self.w_updt is None:
            self.w_updt = np.zeros(np.shape(w))

        self.w_updt = self.momentum * self.w_updt + (1 - self.momentum) * grad_wrt_w
        return w - self.learning_rate * self.w_updt


class NesterovAcceleratedGradient:
    def __init__(self, learning_rate=0.001, momentum=0.4):
        self.learning_rate = learning_rate
        self.momentum = momentum
        self.w_updt = np.array([])

    def update(self, w, grad_func):
        approx_future_grad = np.clip(grad_func(w - self.momentum * self.w_updt), -1, 1)
        if not self.w_updt.any():
            self.w_updt = np.zeros(np.shape(w))

        self.w_updt = self.momentum * self.w_updt + self.learning_rate * approx_future_grad
        return w - self.w_updt


class Adagrad:
    def __init__(self, learning_rate=0.01):
        self.learning_rate = learning_rate
        self.G = None
        self.eps = 1e-8

    def update(self, w, grad_wrt_w):
        if self.G is None:
            self.G = np.zeros(np.shape(w))

        self.G += np.power(grad_wrt_w, 2)
        return w - self.learning_rate * grad_wrt_w / np.sqrt(self.G + self.eps)


class Adadelta:
    def __init__(self, rho=0.95, eps=1e-6):
        self.E_w_updt = None
        self.E_grad = None
        self.w_updt = None
        self.eps = eps
        self.rho = rho

    def update(self, w, grad_wrt_w):
        if self.w_updt is None:
            self.w_updt = np.zeros(np.shape(w))
            self.E_w_updt = np.zeros(np.shape(w))
            self.E_grad = np.zeros(np.shape(grad_wrt_w))

        self.E_grad = self.rho * self.E_grad + (1 - self.rho) * np.power(grad_wrt_w, 2)
        RMS_delta_w = np.sqrt(self.E_w_updt + self.eps)
        RMS_grad = np.sqrt(self.E_grad + self.eps)

        adaptive_lr = RMS_delta_w / RMS_grad

        self.w_updt = adaptive_lr * grad_wrt_w

        self.E_w_updt = self.rho * self.E_w_updt + (1 - self.rho) * np.power(self.w_updt, 2)
        return w - self.w_updt


class RMSprop:
    def __init__(self, learning_rate=0.01, rho=0.9):
        self.learning_rate = learning_rate
        self.Eg = None
        self.eps = 1e-8
        self.rho = rho

    def update(self, w, grad_wrt_w):
        if self.Eg is None:
            self.Eg = np.zeros(np.shape(grad_wrt_w))

        self.Eg = self.rho * self.Eg + (1 - self.rho) * np.power(grad_wrt_w, 2)
        return w - self.learning_rate * grad_wrt_w / np.sqrt(self.Eg + self.eps)


class Adam:
    def __init__(self, learning_rate=0.001, b1=0.9, b2=0.999):
        self.learning_rate = learning_rate
        self.eps = 1e-8
        self.m = None
        self.v = None
        self.b1 = b1
        self.b2 = b2

    def update(self, w, grad_wrt_w):
        if self.m is None:
            self.m = np.zeros(np.shape(grad_wrt_w))
            self.v = np.zeros(np.shape(grad_wrt_w))

        self.m = self.b1 * self.m + (1 - self.b1) * grad_wrt_w
        self.v = self.b2 * self.v + (1 - self.b2) * np.power(grad_wrt_w, 2)

        m_hat = self.m / (1 - self.b1)
        v_hat = self.v / (1 - self.b2)

        return w - self.learning_rate * m_hat / (np.sqrt(v_hat) + self.eps)
