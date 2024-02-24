# Melody generator

This is a code for ESP8266 board that has a passive buzzer connected. This code was made in PlatformIO environment. The ESP8266 is able to play a melody (an array of soundwaves) that was send to respective [ntfy.sh](https://ntfy.sh) topic. The default topic is [melody-generator](https://ntfy.sh/melody-generator).

## Message structure

### Definition

`repeat_count soundwave1_start_frequency soundwave1_end_frequency soundwave1_start_volume soundwave1_end_volume soundwave1_duration soundwave2_start_frequency soundwave2_end_frequency soundwave2_start_volume soundwave2_end_volume soundwave2_duration`

**All arguments are integers.**

- repeat_count - Defines how many times should the melody repeat. When set to 0 the melody will repeat indefinitely.
- soundwavex_start_frequency, soundwavex_end_frequency - During its playback the to frequency changes linearly from start frequency to end frequency. The frequency is defined in hz and can be values from 1hz up to 3000hz.
- soundwavex_start_volume, soundwavex_end_volume - Same as for start end frequency. The volume is a % from 0 to 100.
- soundwavex_duration - Defines duration of the soundwave playback in miliseconds.

### Example

`0 20 3000 100 1 1000 3000 20 1 100 1000`

This message will start an indefinite melody that plays from 20 to 3000hz from 1 to 100% volume in and back in 2000ms.
