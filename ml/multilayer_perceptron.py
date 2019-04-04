from sklearn import datasets
import numpy as np
from sklearn.model_selection import train_test_split

from deep.multilayerperceptron import MultilayerPerceptron
from utils.plot import Plot
from utils.utils import to_categorical, accuracy_score


def main():

    data = datasets.load_digits()
    X = data.data
    y = data.target

    y = to_categorical(y.astype("int"))
    n_hidden = 512

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4)
    clf = MultilayerPerceptron(n_hidden)
    clf.fit(X_train, y_train)
    y_pred = np.argmax(clf.predict(X_test), axis=1)
    y_test = np.argmax(y_test, axis=1)

    accuracy = accuracy_score(y_test, y_pred)
    print(f"Accuracy: {accuracy}")
    Plot().plot_in_2d(X_test, y_pred, title="perceptron", accuracy=accuracy, legend_labels=np.unique(y))


if __name__ == "__main__":
    main()

