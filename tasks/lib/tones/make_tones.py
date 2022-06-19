####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from pathlib import Path

from .generate_wav_tone import generate_wav_tone

####################################################################################################

SHORT_PULSE = 200   # ms
LONG_PULSE = SHORT_PULSE * 3
SHORT_PAUSE = SHORT_PULSE
LONG_PAUSE = SHORT_PAUSE * 5
RISE_TIME = 10   # ms

FREQUENCY = 1000   # Hz
AMPLITUDE = .3

####################################################################################################

def make_tones(ctx, force=False) -> None:

    tones_directory = ctx.build.resources_path.joinpath('tones')
    if not force and tones_directory.exists():
        return
    tones_directory.mkdir(exist_ok=True)

    def td(_):
        return str(tones_directory.joinpath(_))

    generate_wav_tone(td('short-pulse.wav'), frequency=FREQUENCY, amplitude=AMPLITUDE, time=SHORT_PULSE, rise_time=RISE_TIME, fall_time=RISE_TIME)
    generate_wav_tone(td('long-pulse.wav'),  frequency=FREQUENCY, amplitude=AMPLITUDE, time=LONG_PULSE,  rise_time=RISE_TIME, fall_time=RISE_TIME)
    generate_wav_tone(td('short-pause.wav'), frequency=0, amplitude=0, time=SHORT_PAUSE)
    generate_wav_tone(td('long-pause.wav'),  frequency=0, amplitude=0, time=LONG_PAUSE)

    for filename in ('short-pulse', 'long-pulse', 'short-pause', 'long-pause'):
        for extension in ('mp3', 'mp4', 'opus', 'ogg'):
            path = Path(tones_directory, f'{filename}.{extension}')
            path.unlink(missing_ok=True)

        with ctx.cd(tones_directory):
            # -vn disable video
            # -ar samping
            # -ac 2 channels
            # -ab bit rate
            print(f"Generate {filename}.mp3/mp4/ogg")
            ctx.run(f'ffmpeg -i {filename}.wav -vn -ar 44100 -ac 2 -ab 192 -f mp3 {filename}.mp3', hide='both')
            ctx.run(f'ffmpeg -i {filename}.wav -vn -ar 44100 -ac 2 -c:a aac -b:a 128k -f mp4 {filename}.mp4', hide='both')
            ctx.run(f'oggenc -o {filename}.ogg {filename}.wav', hide='both')
            # ffmpeg -i $i.wav $i.opus

####################################################################################################

# aplay
#   long-pulse.wav
#   short-pause.wav
#   short-pulse.wav
#   short-pause.wav
#   long-pulse.wav
#   long-pause.wav
#   short-pulse.wav
