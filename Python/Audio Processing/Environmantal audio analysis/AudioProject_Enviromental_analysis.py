# COMP.SGN.120-2020-2021-1
# Introduction to Audio Processing
# Project work
# Aliisa Nissinen
# Last edited 9.12.2020

import librosa
import numpy as np
from scipy.spatial import distance
import matplotlib.pyplot as plt


# Removes the diagonal (1) values from the matrix
# Given parameter is a cosine_similarity matrix,
# that have 1 as a diagonal values
def remove_diagonal(cosine_similarity):
    no_diagonal = np.delete(cosine_similarity,
                            range(0, cosine_similarity.shape[0] ** 2,
                                  (cosine_similarity.shape[0] + 1)))\
        .reshape(cosine_similarity.shape[0], (cosine_similarity.shape[1] - 1))
    return no_diagonal


# Calculates the an average similarity of all data and prints the result
# obtained
# Given parameter is the cosine_similarity matrix
def avg_similarity_all_data(cosine_similarity):
    cosine_similarity_no_diagonal = remove_diagonal(cosine_similarity)
    avg_similarity_for_all_data = np.mean(cosine_similarity_no_diagonal)
    print('\nAverage similarity between files for all data is ',
          avg_similarity_for_all_data)


# Prints the average similarity of the specific class
# Given parameters are the name of the class and the average similarity
def print_info(tag, avg_similarity_for_class):
    print('Average similarity between files for the class "', tag, '" is ',
          avg_similarity_for_class, sep='')


# Removes the negative (-1) values from the matrix
# Given parameter is the matrix, that contains cosine similarity and values -1
# if the audio doesn't have the specific tag
def remove_negative_values(same_tags_matrix):
    same_tags_matrix = \
        same_tags_matrix[~np.all(same_tags_matrix == -1, axis=1)]
    same_tags_matrix = \
        same_tags_matrix[:, ~np.all(same_tags_matrix == -1, axis=0)]
    return same_tags_matrix


# Calculates the similarity of files in the same class, all audio files are
# categorized in the classes by a tag. One audio can be in several different
# classes.
# Given parameter is the cosine_similarity matrix
def class_avg_similarity(cosine_similarity):
    classes = ['footsteps', 'traffic_noise', 'adults_talking',
               'children_voices', 'announcement_speech', 'music',
               'birds_singing']

    for tag in classes:
        file = open('csv_files/H291603.csv')
        same_tags_matrix = np.copy(cosine_similarity)
        row = 0

        for line in file:
            # First row contains only the headers of the columns
            if row > 0:
                # If the audio doesn't have a specific tag, then that row and
                # the column gets a value -1, those will be removed later
                if line.find(tag) == -1:
                    same_tags_matrix[:, row - 1] = -1
                    same_tags_matrix[row - 1, :] = -1

            row += 1

        file.close()
        same_tags_matrix = remove_negative_values(same_tags_matrix)
        avg_similarity_for_class = np.mean(same_tags_matrix)
        print_info(tag, avg_similarity_for_class)


# Plots the heat map of the cosine_similarity matrix,
# the darker the value is, the more similarity there is
# Given parameter is the cosine_similarity matrix
def plot_heat_map(cosine_similarity):
    plt.imshow(cosine_similarity, cmap='Oranges', interpolation='nearest')
    plt.colorbar()
    plt.title('Heatmap of similarity')
    plt.show()


# Writes the cosine similarity matrix to s_matrix.csv file
# Given parameters are the names of the audio files and cosine
# similarity matrix
def write_matrix(audio_names, cosine_similarity):
    file = open('s_matrix.csv', 'w')

    # The names of the audio files are in the specific order, the same order
    # as the values in the cosine_similarity matrix
    name_calc = 0
    for name in audio_names:
        file.write(name)
        for column in cosine_similarity[name_calc]:
            file.write(',' + str(column))
        file.write('\n')
        name_calc += 1

    file.close()


# Calculates the cosine similarity of each file to each file
# Given parameters are the mfcc features of a file and all audio names
def calc_cosine_similarity(mfcc_features, audio_names):
    similarity = []
    for name in audio_names:
        audio, fs = librosa.load('audio_files/' + name)
        mfcc_compare = calc_mfcc(audio, fs)
        mfcc_features_compare = calc_features(mfcc_compare)
        cosine = 1 - distance.cosine(mfcc_features, mfcc_features_compare)
        similarity = np.append(similarity, cosine)

    return similarity


# Calculates the features of the MFCC, the mean and the std
# Given parameter is the mfcc
def calc_features(mfcc):
    features = []
    for line in mfcc:
        features = np.append(features, np.mean(line))
        features = np.append(features, np.std(line))
    return features


# Calculates the MFCC
# Given parameters are the audio and its sample rate
def calc_mfcc(audio, fs):
    mfcc = librosa.feature.mfcc(y=audio, sr=fs, S=None, n_mfcc=40,
                                norm='ortho', n_fft=512)
    return mfcc


# Calculates a similarity matrix between the files
# Given parameter is vector that contains the names of the audio files
def files_similarity(audio_names):
    cosine_similarity = \
        np.zeros(shape=[len(audio_names), len(audio_names)])

    # rows in the cosine_similarity matrix,
    # in the end is equal to the size of audio names vector - 1
    row = 0
    for name in audio_names:
        audio, fs = librosa.load('audio_files/' + name)
        mfcc = calc_mfcc(audio, fs)
        mfcc_features = calc_features(mfcc)
        cosine_similarity[row] = \
            calc_cosine_similarity(mfcc_features, audio_names)
        row += 1
    return cosine_similarity


# Reading the names of audio files in specific order and
# save them in the vector
def read_names():
    file = open('csv_files/H291603.csv')

    audio_names = []
    row = 0
    for line in file:
        # First row contains only the headers of the columns
        if row > 0:
            filename = line[:line.index('.mp3')] + '.wav'
            audio_names.append(filename)
        row += 1

    file.close()
    return audio_names


def main():
    audio_names = read_names()
    cosine_similarity = files_similarity(audio_names)
    write_matrix(audio_names, cosine_similarity)
    plot_heat_map(cosine_similarity)

    class_avg_similarity(cosine_similarity)

    avg_similarity_all_data(cosine_similarity)


main()
