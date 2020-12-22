# DATA.ML.100-2020-2021-1
# Introduction to Patter Recognition and Machine Learning
# Exercise 4
# Aliisa Nissinen
# Last edited 8.10.2020


import pickle
import numpy as np
import matplotlib.pyplot as plt
from random import random
from time import process_time
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import Conv2D
from tensorflow.keras.layers import MaxPooling2D
from tensorflow.keras.layers import Dropout
import keras


def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict


def onehot_10vector(Y):
    return tf.keras.utils.to_categorical(Y)


def class_acc(c, Y):
    acc = np.mean(c == Y) * 100
    acc = round(acc, 2)
    return acc


def main():
    datadict = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/test_batch')
    datadict_train1 = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/data_batch_1')
    datadict_train2 = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/data_batch_2')
    datadict_train3 = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/data_batch_3')
    datadict_train4 = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/data_batch_4')
    datadict_train5 = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/data_batch_5')

    X = datadict["data"]
    Y = datadict["labels"]
    X_train = np.concatenate([datadict_train1["data"],
                              datadict_train2["data"],
                              datadict_train3["data"],
                              datadict_train4["data"],
                              datadict_train5["data"]])
    Y_train = np.concatenate([datadict_train1["labels"],
                              datadict_train2["labels"],
                              datadict_train3["labels"],
                              datadict_train4["labels"],
                              datadict_train5["labels"]])

    labeldict = unpickle \
        ('/Users/aliisanissinen/Downloads/cifar-10-batches-py/batches.meta')
    label_names = labeldict["label_names"]

    X = X.astype("float32") / 255.0
    Y = np.array(Y)
    X_train = X_train.astype("float32") / 255.0
    Y_train = np.array(Y_train)

    Y_train = onehot_10vector(Y_train)
    Y = onehot_10vector(Y)

    # one layer of 5 neuros
    start = process_time()
    model = Sequential()
    model.add(Dense(5, input_shape=(32*32*3,), activation="sigmoid"))
    model.add(Dense(10, activation="sigmoid"))
    model.compile(optimizer=keras.optimizers.SGD(lr=0.001),
                  loss="categorical_crossentropy",
                  metrics=["accuracy"])
    fitmodel = \
        model.fit(X_train, Y_train, batch_size=100, epochs=100,
                  validation_data=(X, Y))
    acc = model.evaluate(X, Y, verbose=1)
    stop = process_time()
    print('Accuracy for one layer of 5 neuros: %.3f' % (acc[1] * 100.0))
    print(f"Elapsed time: {stop - start}")

    # one layer of 10 neuros
    start = process_time()
    model = Sequential()
    model.add(Dense(10, input_shape=(32 * 32 * 3,), activation="sigmoid"))
    model.add(Dense(10, activation="sigmoid"))
    model.compile(optimizer=keras.optimizers.SGD(lr=0.001),
                  loss="categorical_crossentropy",
                  metrics=["accuracy"])
    fitmodel = \
        model.fit(X_train, Y_train, batch_size=100, epochs=100,
                  validation_data=(X, Y))
    acc = model.evaluate(X, Y, verbose=1)
    stop = process_time()
    print('Accuracy for one layer of 10 neuros: %.3f' % (acc[1] * 100.0))
    print(f"Elapsed time: {stop - start}")

    # more than one layers of 10000 neuros
    start = process_time()
    model = Sequential()
    model.add(Dense(10000, input_shape=(32 * 32 * 3,), activation="sigmoid"))
    model.add(Dense(1000, activation="sigmoid"))
    model.add(Dense(100, activation="sigmoid"))
    model.add(Dense(10, activation="sigmoid"))
    model.compile(optimizer=keras.optimizers.SGD(lr=0.001),
                  loss="categorical_crossentropy",
                  metrics=["accuracy"])
    fitmodel = \
        model.fit(X_train, Y_train, batch_size=100, epochs=100,
                  validation_data=(X, Y))
    acc = model.evaluate(X, Y, verbose=1)
    stop = process_time()
    print('Accuracy for more than one layers of 10000 neuros:'
          ' %.3f' % (acc[1] * 100.0))
    print(f"Elapsed time: {stop - start}")

    # convolutional layer
    X_train = X_train.reshape(50000, 32, 32, 3)
    X = X.reshape(10000, 32, 32, 3)
    start = process_time()
    model = Sequential()
    model.add(keras.Input(shape=(32, 32, 3)))
    model.add(Conv2D(32, (3, 3), activation="relu"))
    model.add(Conv2D(32, (3, 3), activation="relu"))
    model.add(Conv2D(64, (3, 3), activation="relu"))
    model.add(Conv2D(64, (3, 3), activation="relu"))
    model.add(Conv2D(128, (3, 3), activation="relu"))
    model.add(Conv2D(128, (3, 3), activation="relu"))
    model.add(keras.layers.Flatten())
    model.add(Dense(128, activation="relu"))
    model.add(Dense(10, activation="sigmoid"))
    model.compile(optimizer=keras.optimizers.SGD(lr=0.001),
                  loss="categorical_crossentropy",
                  metrics=["accuracy"])
    fitmodel = \
        model.fit(X_train, Y_train, batch_size=100, epochs=100,
                  validation_data=(X, Y))
    acc = model.evaluate(X, Y, verbose=1)
    stop = process_time()
    print('Accuracy for 3 convolutional layers:'
          ' %.3f' % (acc[1] * 100.0))
    print(f"Elapsed time: {stop - start}")

    # plot loss
    plt.figure(figsize=(6, 7))
    plt.subplot(211)
    plt.title('Cross Entropy Loss')
    plt.plot(fitmodel.history['loss'], color='blue', label='train')
    plt.plot(fitmodel.history['val_loss'], color='orange', label='test')
    # plot accuracy
    plt.subplot(212)
    plt.title('Classification Accuracy')
    plt.plot(fitmodel.history['accuracy'], color='blue', label='train')
    plt.plot(fitmodel.history['val_accuracy'], color='orange', label='test')
    plt.show()


main()
