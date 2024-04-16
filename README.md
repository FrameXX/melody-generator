# Melody generator

This is a code for ESP8266 board that has a passive buzzer connected. This code was made in PlatformIO environment. The ESP8266 is able to play a melody (an array of soundwaves) that was send to respective [ntfy.sh](https://ntfy.sh) topic. The default topic is [melody-generator](https://ntfy.sh/melody-generator).

## Message structure

### Definition

`repeat_count soundwave1_frequency soundwave1_duration soundwave2_frequency soundwave2_duration ...`

**All arguments are integers.**

- repeat_count - Defines how many times should the melody repeat. When set to 0 the melody will repeat indefinitely.
- soundwave_frequency - Defines frequency of the played soundwave in seconds.
- soundwave_duration - Defines duration of the soundwave playback in miliseconds.

### Example

`0 300 300 500 300`

This will play a simple "buup beep" in a fast succession infinitely.
