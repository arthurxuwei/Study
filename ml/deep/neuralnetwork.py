import numpy as np

from utils.utils import batch_iterator


class NeuralNetwork:
    """
    Neural Network. Deep learning base model
    """
    def __init__(self, optimizer, loss, validation_data=None):
        self.optimizer = optimizer
        self.layers = []
        self.errors = {"training": [], "validation": []}
        self.loss_function = loss()
        self.val_set = None
        if validation_data:
            X, y = validation_data
            self.val_set = {"X": X, "y": y}

    def set_trainable(self, trainable):
        """
        Method which enables freezing of the weights of the network's layers
        """
        for layer in self.layers:
            layer.trainable = trainable

    def add(self, layer):
        """
        Method which adds a layer
        :param layer:
        :return:
        """
        if self.layers:
            # set the input shape to the output shape of the last added layer
            layer.set_input_shape(shape=self.layers[-1].output_shape())

        if hasattr(layer, 'initialize'):
            layer.initialize(optimizer=self.optimizer)

        self.layers.append(layer)

    def _forward_pass(self, X, training=True):
        """
        Calculate the output of the NN
        """
        layer_output = X
        for layer in self.layers:
            layer_output = layer.forward_pass(layer_output, training)
        return layer_output

    def _backward_pass(self, loss_grad):
        """
        Propagate the gradient 'backwards' and update the weights in each layer
        """
        for layer in reversed(self.layers):
            loss_grad = layer.backward_pass(loss_grad)

    def test_on_batch(self, X, y):
        """
        Evaluates the model over a single batch of samples
        """
        y_pred = self._forward_pass(X, training=False)
        loss = np.mean(self.loss_function.loss(y, y_pred))
        acc = self.loss_function.acc(y, y_pred)
        return loss, acc

    def train_on_batch(self, X, y):
        """
        Single gradient update over one batch of samples
        """
        y_pred = self._forward_pass(X)
        loss = np.mean(self.loss_function.loss(y, y_pred))
        acc = self.loss_function.acc(y, y_pred)
        # Calculate the gradient of the loss function wrt y_pred
        loss_grad = self.loss_function.gradient(y, y_pred)
        self._backward_pass(loss_grad=loss_grad)
        return loss, acc

    def fit(self, X, y, n_epochs, batch_size):
        """
        Trains the model for a fixed number of epochs
        """
        for _ in range(n_epochs):
            batch_error = []
            for X_batch, y_batch in batch_iterator(X, y, batch_size=batch_size):
                loss, _ = self.train_on_batch(X_batch, y_batch)
                batch_error.append(loss)

            self.errors["training"].append(np.mean(batch_error))

            if self.val_set is not None:
                val_loss, _ = self.test_on_batch(self.val_set["X"], self.val_set["y"])
                self.errors["validation"].append(val_loss)
        return self.errors["training"], self.errors["validation"]

    def predict(self, X):
        return self._forward_pass(X, training=False)

    def summary(self, name="Model Summary"):
        print(name)
        print(f"Input shape: {self.layers[0].input_shape}")
        for layer in self.layers:
            print(f"layer_name: {layer.layer_name()}, "
                  f"params: {layer.parameters()}, "
                  f"out shape: {layer.output_shape()}")
