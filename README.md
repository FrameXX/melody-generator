# Melody generator

This is a code for ESP8266 board that has a passive buzzer connected. The ESP8266 is able to play a melody (an array of tones) that was send to respective [ntfy.sh](https://ntfy.sh) topic. The default topic is [melody-generator](https://ntfy.sh/melody-generator).

## Message structure

### Definition

`repeat_count tone1_start_frequency tone1_end_frequency tone1_start_volume tone1_end_volume tone1_duration tone2_start_frequency tone2_end_frequency tone2_start_volume tone2_end_volume tone2_duration`

**All arguments are integers.**

- repeat_count - Defines how many times should the melody repeat. When set to 0 the melody will repeat indefinitely.
- tonex_start_frequency, tonex_end_frequency - During its playback the to frequency changes linearly from start frequency to end frequency. The frequency is defined in hz and can be values from 1hz up to 3000hz.
- tonex_start_volume, tonex_end_volume - Same as for start end frequency. The volume is a % from 0 to 100.
- tonex_duration - Defines duration of the tone playback in miliseconds.

### Example

`0 20 3000 100 1 1000 3000 20 1 100 1000`

This message will start an indefinite melody that plays from 20 to 3000hz from 1 to 100% volume in and back in 2000ms.
