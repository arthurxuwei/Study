import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

from deep.layers import Conv2D, Activation, Dropout, BatchNormalization, Flatten, Dense
from deep.loss_functions import CrossEntropy
from deep.neuralnetwork import NeuralNetwork
from deep.optimizers import Adam
from utils.plot import Plot
from utils.utils import to_categorical


def main():
    optimizer = Adam()
    data = datasets.load_digits()
    X = data.data
    y = data.target

    y = to_categorical(y.astype("int"))

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4)

    X_train = X_train.reshape((-1, 1, 8, 8))
    X_test = X_test.reshape((-1, 1, 8, 8))

    clf = NeuralNetwork(optimizer=optimizer, loss=CrossEntropy, validation_data=(X_test, y_test))
    clf.add(Conv2D(n_filters=16, filter_shape=(3, 3), stride=1, input_shape=(1, 8, 8), padding='same'))
    clf.add(Activation('relu'))
    clf.add(Dropout(0.25))
    clf.add(BatchNormalization())
    clf.add(Conv2D(n_filters=32, filter_shape=(3, 3), stride=1, padding='same'))
    clf.add(Activation('relu'))
    clf.add(Dropout(0.25))
    clf.add(BatchNormalization())
    clf.add(Flatten())
    clf.add(Dense(256))
    clf.add(Activation('relu'))
    clf.add(Dropout(0.4))
    clf.add(BatchNormalization())
    clf.add(Dense(10))
    clf.add(Activation('softmax'))

    clf.summary(name="ConvNet")

    train_err, val_err = clf.fit(X_train, y_train, n_epochs=50, batch_size=256)

    # Training and validation error plot
    n = len(train_err)
    training, = plt.plot(range(n), train_err, label="Training Error")
    validation, = plt.plot(range(n), val_err, label="Validation Error")
    plt.legend(handles=[training, validation])
    plt.title("Error Plot")
    plt.ylabel('Error')
    plt.xlabel('Iterations')
    plt.show()

    _, accuracy = clf.test_on_batch(X_test, y_test)
    print("Accuracy:", accuracy)

    y_pred = np.argmax(clf.predict(X_test), axis=1)
    X_test = X_test.reshape(-1, 8*8)
    # Reduce dimension to 2D using PCA and plot the results
    Plot().plot_in_2d(X_test, y_pred, title="Convolutional Neural Network", accuracy=accuracy, legend_labels=range(10))


if __name__ == "__main__":
    main()
