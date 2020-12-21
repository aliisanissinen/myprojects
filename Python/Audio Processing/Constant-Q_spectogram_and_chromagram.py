# COMP.SGN.120-2020-2021-1
# Introduction to Audio Processing course
# Exercise 6
# Aliisa Nissinen
# Last edited 7.12.2020

import librosa
import librosa.display
import sounddevice as sd
import numpy as np
from matplotlib import pyplot as plt


def specshows(audio, fs):
    spectrogram = \
        librosa.amplitude_to_db(abs(librosa.core.stft(audio)), ref=np.max)
    constantQ = \
        librosa.amplitude_to_db(abs(librosa.core.cqt(audio, sr=fs)), ref=np.max)
    chroma = librosa.feature.chroma_stft(audio, fs)

    plt.subplot(3, 1, 1)
    librosa.display.specshow(spectrogram)
    plt.ylabel('Frequency (Hz)')
    plt.xlabel('Time (s)')
    plt.colorbar(format='%+2.0f dB')
    plt.title('Linear-frequency power spectrogram')

    plt.subplot(3, 1, 2)
    librosa.display.specshow(constantQ)
    plt.ylabel('Frequency (Hz)')
    plt.xlabel('Time (s)')
    plt.colorbar(format='%+2.0f dB')
    plt.title('Constant-Q power spectrogram (note)')

    plt.subplot(3, 1, 3)
    librosa.display.specshow(chroma)
    plt.ylabel('Pitch class')
    plt.xlabel('Time (s)')
    plt.colorbar()
    plt.title('Chromagram')
    plt.tight_layout()
    plt.show()


def main():
    audio, fs = librosa.load('brahms_hungarian_dance_5_short.wav')
    sd.play(audio, blocking=True)
    specshows(audio, fs)

    audio, fs = librosa.load('classic_rock_beat.wav')
    sd.play(audio, blocking=True)
    specshows(audio, fs)

    audio, fs = librosa.load('conga_groove.wav')
    sd.play(audio, blocking=True)
    specshows(audio, fs)

    audio, fs = librosa.load('latin_groove_short.wav')
    sd.play(audio, blocking=True)
    specshows(audio, fs)


main()

