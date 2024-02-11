# Melody generator

This is a code for ESP8266 board that has a passive buzzer connected. The ESP8266 is able to play a melody (an array of tones) that was send to respective [ntfy.sh](https://ntfy.sh) topic. The default topic is [melody-generator](https://ntfy.sh/melody-generator).

## Message structure

`repeat repeat_count tone1_start_frequency tone1_end_frequency tone1_start_volume tone1_end_volume tone1_duration tone2_start_frequency tone2_end_frequency tone2_start_volume tone2_end_volume tone2_duration`

- repeat: boolean
  - defines whether to repeat the melody or play it just
