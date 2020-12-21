# COMP.SGN.120-2020-2021-1
# Introduction to Audio Processing
# Exercise 6
# Aliisa Nissinen
# Last edited 7.12.2020

import librosa
import librosa.display
import librosa.util
import sounddevice as sd
import numpy as np
from matplotlib import pyplot as plt


def process(audio, fs):
    spectrogram = \
        librosa.amplitude_to_db(abs(librosa.core.stft(audio)), ref=np.max)
    spectral_novelty = librosa.onset.onset_strength(audio, sr=fs)
    peaks = librosa.util.peak_pick(spectral_novelty, 1, 1, 1, 1, 1, 1)
    times = librosa.frames_to_time(np.arange(len(spectral_novelty)), sr=fs)

    plt.subplot(2, 1, 1)
    librosa.display.waveplot(audio)
    plt.xlabel('Time')
    plt.ylabel('Amplitude')
    plt.vlines(times[peaks], audio.min(), audio.max(), color='r')

    plt.subplot(2, 1, 2)
    librosa.display.specshow(spectrogram, x_axis='time', y_axis='log')
    plt.xlabel('Time')
    plt.ylabel('Hz')
    plt.vlines(times[peaks], 0, 10000, color='r')
    plt.show()

    clicks = librosa.clicks(frames=peaks, sr=fs, length=len(audio))
    sd.play(audio + clicks, blocking=True)
    # sd.play(np.vstack([audio, clicks]), blocking=True)


def main():
    audio, fs = librosa.load('classic_rock_beat.wav')
    sd.play(audio, blocking=True)
    process(audio, fs)

    audio, fs = librosa.load('brahms_hungarian_dance_5_short.wav')
    sd.play(audio, blocking=True)
    process(audio, fs)

    audio, fs = librosa.load('conga_groove.wav')
    sd.play(audio, blocking=True)
    process(audio, fs)

    audio, fs = librosa.load('latin_groove_short.wav')
    sd.play(audio, blocking=True)
    process(audio, fs)


main()

