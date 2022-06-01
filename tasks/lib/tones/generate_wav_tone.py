#! /usr/bin/env python3

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
#
####################################################################################################

####################################################################################################

# https://en.wikipedia.org/wiki/WAV
# https://fr.wikipedia.org/wiki/Waveform_Audio_File_Format

####################################################################################################

import wave

import numpy as np

####################################################################################################

class ToneGenerator:

    ##############################################

    def __init__(self,
                frequency=440, # Hz LA3 A4
                amplitude=1.,
    ):

        self._frequency = frequency
        self._amplitude = amplitude

    ##############################################

    def generate(self, times):

        pulsation = 2 * np.pi * self._frequency
        pcm = self._amplitude * np.sin(pulsation * times)
        return pcm

####################################################################################################

class WavFile:

    ##############################################

    def __init__(self,
                 sample_rate=44100, # Hz
                 number_of_bits=16,
                 number_of_channels=2,
                 duration=1, # s
                 rise_time=100, # ms
                 fall_time=100,
    ):

        self._sample_rate = sample_rate
        self._number_of_bits = number_of_bits
        self._number_of_channels = number_of_channels
        self._duration = duration
        self._rise_time = rise_time
        self._fall_time = fall_time

        self._sampling_period = 1 / self._sample_rate

    ##############################################

    def make_t(self, i_start, i_stop):

        # stop = start + size * self._sampling_period
        # times = np.arange(start, stop, self._sampling_period)
        # return times[:size]

        # return np.arange(start, stop, self._sampling_period)

        return np.arange(i_start, i_stop) *  self._sampling_period

    ##############################################

    def encode_frames(self, pcm, to_stereo=False):

        if self._number_of_bits:
            dtype = '<i2'
        else:
            raise NotImplementedError

        mono_frames = np.array(pcm, dtype=dtype)
        if to_stereo:
            stereo_frames = np.zeros(2 * mono_frames.size, dtype=dtype)
            stereo_frames[0:-1:2] = mono_frames
            stereo_frames[1::2] = mono_frames
            frames = stereo_frames
        else:
            frames = mono_frames

        return frames.tobytes('C')

    ##############################################

    def make_wave(self, path, tone_generator):

        wave_file = wave.open(path, 'wb')

        sample_width = self._number_of_bits // 8
        number_of_frames = int(self._sample_rate * self._duration)
        # (nchannels, sampwidth, framerate, nframes, comptype, compname)
        wave_file.setparams((self._number_of_channels,
                             sample_width,
                             self._sample_rate,
                             number_of_frames,
                             'NONE',
                             'not compressed'))

        # 16-bit = 32767
        amplitude_max = 2 ** self._number_of_bits // 2 - 1

        chunk_size = 10000
        time_window = chunk_size * self._sampling_period
        for chunk in range(number_of_frames // 1000 + 2):
            i_start = chunk * chunk_size
            i_stop = i_start + chunk_size
            start = i_start * self._sampling_period
            stop = min(i_stop * self._sampling_period, self._duration)
            i_stop = int(stop / self._sampling_period)
            times = self.make_t(i_start, i_stop)
            # print(chunk, i_start, i_stop,  stop, times)
            pcm = tone_generator.generate(times)
            if start < self._rise_time:
                pcm *= np.minimum(times / self._rise_time, np.ones(times.size))
            if stop > self._duration - self._fall_time:
                pcm *= np.minimum(- (times - self._duration) / self._fall_time, np.ones(times.size))
            pcm *= amplitude_max
            frames = self.encode_frames(pcm, to_stereo=self._number_of_channels == 2)
            wave_file.writeframes(frames) # writeframesraw
            if stop == self._duration:
                break

        wave_file.close()

####################################################################################################

def generate_wav_tone(
        filename: str,
        frequency: float = 440.0,   # LA3 A4
        amplitude: float = 1.,
        time: int = 1.,   # ms
        rise_time: int = 100.,   # ms
        fall_time: int = 100.,   # ms
        rate: int = 44100,   # Hz
        bits: int = 16,
        channels: int = 2,
) -> None:

    print(f"Generate {filename}")
    wav_file = WavFile(
        sample_rate=rate,
        number_of_bits=bits,
        number_of_channels=channels,
        duration=time / 1000,
        rise_time=rise_time / 1000,
        fall_time=fall_time / 1000,
    )
    tone_generator = ToneGenerator(
        frequency=frequency,
        amplitude=amplitude,
    )
    wav_file.make_wave(filename, tone_generator)

####################################################################################################

if __name__ == "__main__":

    import argparse

    # cut at 14.7 kHz ???

    argument_parser = argparse.ArgumentParser()

    argument_parser.add_argument('-r', '--rate', help="Sample rate in Hz",
                                 type=int, default=44100)

    argument_parser.add_argument('-b', '--bits', help="Number of bits in each sample",
                                 type=int, choices=(16,), default=16)

    argument_parser.add_argument('-c', '--channels', help="Number of channels to produce",
                                 type=int, default=2)

    argument_parser.add_argument('-t', '--time', help="Duration of the wave in ms.",
                                 type=float, default=1.)

    argument_parser.add_argument('-rt', '--rise-time', help="Rise time in ms.",
                                 type=float, default=100.)

    argument_parser.add_argument('-ft', '--fall-time', help="Fall time is ms.",
                                 type=float, default=100.)

    argument_parser.add_argument('-a', '--amplitude', help="Amplitude of the wave on a scale of 0.0-1.0.",
                                 type=float, default=1,)

    argument_parser.add_argument('-f', '--frequency', help="Frequency of the wave in Hz",
                                 type=float, default=440.0) # LA3 A4

    argument_parser.add_argument('filename', help="The file to generate.")

    args = argument_parser.parse_args()

    generate_wav_tone(
        args.filename,
        frequency=args.frequency,
        amplitude=args.amplitude,
        time=args.time,
        rise_time=args.rise_time,
        fall_time=args.fall_time,
        rate=args.rate,
        bits=args.bits,
        channels=args.channels,
    )
