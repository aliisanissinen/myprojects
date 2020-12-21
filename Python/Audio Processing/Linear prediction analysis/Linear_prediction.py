# COMP.SGN.120-2020-2021-1
# Introduction to Audio Processing course
# Exercise 4
# Aliisa Nissinen
# Last edited 23.11.2020


import numpy as np
import scipy
from numpy.fft import fft, ifft, fftshift, fftfreq
import soundfile as sf
import scipy.signal
from scipy.signal import hamming, hann
from matplotlib import pyplot as plt
from audiolazy import lazy_lpc as lpc


# Given with exercise instructions
def est_predictor_gain(x, a, p):
    """
    A function to compute gain of the residual signal in LP analysis.
    x:  signal
    a: LPC coefficients
    p: order of the filter
    """
    cor = np.correlate(x, x, mode='full')
    rr = cor[len(cor)//2: len(cor)//2+p+1]
    g = np.sqrt(np.sum(a*rr))
    return g


# Given with exercise instructions
def reject_outliers(data, m=2):
    """
    Function to reject outliers. All values beyond m standard deviations
    from means are excluded
    """
    return data[abs(data - np.mean(data)) < m * np.std(data)]


def main():

    audioIn, fs = sf.read('o.wav')
    audioOut = np.zeros(len(audioIn))
    p = 16  # has to be tuned
    nfft = 1024
    inInd = 0
    outInd = 0
    wLen = int(0.02*fs)
    win = hamming(wLen)
    wHop = int(0.01*fs)

    cnt = 0
    numFrames = np.ceil((len(audioIn)-wLen)/(wLen/2))
    formants = []

    # choose a representative frame of the vowel
    plot_frame = int(numFrames/2)  # middle of the vowel

    # The analysis loop
    while inInd < len(audioIn)-wLen:

        frame = audioIn[inInd:inInd+wLen] * win

        LPC = lpc.lpc.autocor(frame, p)
        gain = est_predictor_gain(frame, LPC.numerator, p)

        w, h = scipy.signal.freqz(gain, LPC.numerator)

        f = fft(fftshift(frame))

        roots = np.roots(LPC.numerator)
        rootsPos = roots[np.where(roots.imag > 0)]

        angz = np.arctan2(np.imag(rootsPos), np.real(rootsPos))
        angz = angz*(fs/(2*np.pi))
        angz = np.sort(angz)
        angz = angz[angz != 0]

        formants.append(angz[:3])

        inInd = inInd + int(wLen/2)
        outInd = outInd + wHop
        cnt = cnt+1

        if cnt == plot_frame:
            plt.figure()
            freq_f = np.linspace(0, fs/2, len(frame)//2)
            plt.plot(freq_f, 10 * np.log10(np.abs(f)[:len(f) // 2]),
                     color="blue")
            freq_h = np.linspace(0, fs / 2, len(h))
            plt.plot(freq_h, 10 * np.log10(h), color="red")
            plt.title("I vowel, p={:d}".format(p))
            plt.show()

    formants = np.array(formants)

    print('Vowel O, The computed formants are :', np.mean(formants, 0))

    plt.plot(formants)
    plt.show()
    formants = reject_outliers(formants)
    plt.plot(formants)
    plt.show()


main()

