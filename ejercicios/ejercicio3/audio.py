#!/usr/bin/env python3

from playsound import playsound
import numpy as np
import struct
import wave

def write_audio_file(loc, data, fs=44100):
    '''
    Write an Audio File in .wav format
    Parameters
    ----------
    loc: string
        Filename location
    data: list
        List of samples in floating-point (normalised from 0-1)
    fs: int, float
        Sampling rate
    '''
    intconst = 32767
    audiof = wave.open(loc, 'w')
    audiof.setnchannels(1)  # mono
    audiof.setsampwidth(2)  # two bytes per sample
    audiof.setframerate(fs)
    for sample in data:
        data = struct.pack('<h', int(sample * intconst))
        audiof.writeframesraw(data)
    audiof.close()


def read_audio_file(loc):
    '''
    Reads a .wav file
    Parameters
    ----------
    loc: string
        File location
    Returns
    -------
    data: list
        samples
    fs: int
        sampling rate
    '''
    intconst = 32767
    data = []
    audiof = wave.open(loc, 'r')

    length = audiof.getnframes()
    for i in range(0, length):
        wavedata = audiof.readframes(1)
        data.append(float(struct.unpack("<h", wavedata)[0]) / intconst)

    audiof.close()

    return data, audiof.getframerate()

def play_audio (loc):
    playsound(loc)


if __name__ == "__main__":
    # Some parameters
    f = 200       # the sound is 200 Hz
    fs = 44100    # common sampling rate
    duration = 1  # in secs
    nsamples = int(duration * fs)
    loc = 'sample.wav'

    # Create a sound
    x = np.arange(0, nsamples)
    samples = list(np.sin(2 * np.pi * (f / fs) * x))

    # Write audio file
    write_audio_file(loc, samples, fs)

    # Play
    play_audio(loc)

    # Read audio file
    rsamples, rfs = read_audio_file(loc)

    print("Input fs:", fs, "Read fs:", rfs)

    def check(exp, ref):
        passed = True
        for i in range(len(ref)):
            if (abs(exp[i] - ref[i]) > 1e-4):
                passed = False
        return passed
    
    if (check(rsamples, samples)):
        print("Test passed")
    else:
        print("Test failed")
