from sklearn import datasets
import numpy as np
from sklearn.model_selection import train_test_split

from deep.activations_functions import Sigmoid
from deep.loss_functions import CrossEntropy
from deep.perceptron import Perceptron
from utils.utils import normalize, to_categorical, accuracy_score


def main():
    data = datasets.load_digits()
    X = normalize(data.data)
    y = data.target

    # data preprocess: One-hot encoding of nominal y-values
    y = to_categorical(y)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33)

    clf = Perceptron(n_iterations=5000, learning_rate=0.001, loss=CrossEntropy, activation_function=Sigmoid)
    clf.fit(X_train, y_train)

    y_pred = np.argmax(clf.predict(X_test), axis=1)
    y_test = np.argmax(y_test, axis=1)

    accuracy = accuracy_score(y_test, y_pred)
    print(f"Accuracy: {accuracy}")


if __name__ == "__main__":
    main()
