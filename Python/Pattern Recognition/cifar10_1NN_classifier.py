# DATA.ML.100-2020-2021-1
# Introduction to Patter Recognition and Machine Learning
# Exercise 2
# Aliisa Nissinen
# Last edited 19.9.2020


import pickle
import numpy as np
import matplotlib.pyplot as plt
from random import random
from time import process_time


def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict


# computes the classification accuracy
def class_acc(pred, gt):
    acc = np.mean(pred == gt) * 100
    acc = round(acc, 2)
    return acc


# returns random class labels (numbers between 0-9)
def cifar10_classifier_random(x):
    random_labels = np.random.randint(0, 9, len(x))
    return random_labels


# 1NN classifier that finds the best match of the input
def cifar10_classifier_1nn(x, trdata, trlabels, L1=True):
    trdata = trdata.reshape(trdata.shape[0], 32 * 32 * 3).astype("float")
    x = x.reshape(x.shape[0], 32 * 32 * 3).astype("float")
    pred_labels = np.zeros(x.shape[0], dtype=trlabels.dtype)
    for i in range(x.shape[0]):
        if (L1):
            dist = np.sum(np.abs(trdata - x[i, :]), axis=1)
        else:
            dist = np.sqrt(np.sum(np.square(trdata - x[i, :]), axis=1))
        min_dist = np.argmin(dist)
        pred_labels[i] = trlabels[min_dist]
    return pred_labels


def main():
    datadict_test = unpickle \
        ('/cifar-10-batches-py/test_batch')
    datadict = unpickle \
        ('/cifar-10-batches-py/data_batch_1')

    X_test = datadict_test["data"]
    Y_test = datadict_test["labels"]
    X = datadict["data"]
    Y = datadict["labels"]

    labeldict = unpickle \
        ('cifar-10-batches-py/batches.meta')
    label_names = labeldict["label_names"]

    X_test = \
      X_test.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype("int32")
    Y_test = np.array(Y_test)

    X = X.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype("int32")
    Y = np.array(Y)

    for i in range(X_test.shape[0]):
        # Show some images randomly
        if random() > 0.999:
            plt.figure(1)
            plt.clf()
            plt.imshow(X_test[i])
            plt.title \
                (f"Image {i} label={label_names[Y_test[i]]} (num {Y_test[i]})")
            plt.pause(1)

    # Accuracy when all labels are right, must give 100%
    start = process_time()
    print(f"Accuracy for right predicted labels: "
          f"{class_acc(Y_test, Y_test)} %")
    stop = process_time()
    print(f"Elapsed time: {stop - start}")

    # Accuracy when all labels are randomly chosen
    start = process_time()
    Y_random = cifar10_classifier_random(X_test)
    print(f"Accuracy for randomly predicted labels: "
          f"{class_acc(Y_random, Y_test)} %")
    stop = process_time()
    print(f"Elapsed time: {stop - start}")

    # Accuracy when all labels are computed with 1NN L1
    start = process_time()
    Y_1NN = cifar10_classifier_1nn(X_test, X, Y)
    print(f"Accuracy for 1NN (L1) predicted labels: "
          f"{class_acc(Y_1NN, Y_test)} %")
    stop = process_time()
    print(f"Elapsed time: {stop - start}")

    # Accuracy when all labels are computed with 1NN L2
    start = process_time()
    Y_1NN = cifar10_classifier_1nn(X_test, X, Y, False)
    print(f"Accuracy for 1NN (L2) predicted labels: "
          f"{class_acc(Y_1NN, Y_test)} %")
    stop = process_time()
    print(f"Elapsed time: {stop - start}")


main()
