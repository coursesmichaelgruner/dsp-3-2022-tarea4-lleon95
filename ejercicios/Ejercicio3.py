#!/usr/bin/env python3

from scipy import signal
import matplotlib.pyplot as plt

from ejercicio3.audio import read_audio_file, play_audio, write_audio_file

def get_filter_coefficients (alpha, k):
    '''
    Gets the coefficients (in arrays)
    '''
    x = [1 - alpha]
    y = [0 for i in range(k)]
    y[0] = 1
    y[k-1] = -alpha
    return x, y

def apply_filter(x, y, sample):
    '''
    Filter sample.
    '''
    return signal.lfilter(x, y, sample)

if __name__ == "__main__":
    # Some parameters
    loc = '../programa/test.wav'

    # Play
    print("Original")
    play_audio(loc)

    data, fs = read_audio_file(loc)

    # Prepare filters and apply
    x, y = get_filter_coefficients(0.6, int(fs * 0.050))
    data1 = apply_filter(x, y, data)
    file = 'test' + str(1)
    write_audio_file(file, data1, fs)
    print("Filter 1")
    play_audio(file)
    x, y = get_filter_coefficients(0.4, int(fs * 0.250))
    data2 = apply_filter(x, y, data)
    file = 'test' + str(2)
    write_audio_file(file, data2, fs)
    print("Filter 2")
    play_audio(file)
    x, y = get_filter_coefficients(0.2, int(fs * 0.50))
    data3 = apply_filter(x, y, data)
    file = 'test' + str(3)
    write_audio_file(file, data3, fs)
    print("Filter 3")
    play_audio(file)

    plt.figure(1)
    plt.plot(data)
    plt.title('Original')
    plt.figure(2)
    plt.plot(data1)
    plt.title('k = 0.05 * Fs, a = 0.6')
    plt.figure(3)
    plt.plot(data2)
    plt.title('k = 0.25 * Fs, a = 0.4')
    plt.figure(4)
    plt.plot(data3)
    plt.title('k = 0.50 * Fs, a = 0.2')
    plt.legend()
    plt.show()

    # It should behave like a LPF
    print(len(data), fs)
    
