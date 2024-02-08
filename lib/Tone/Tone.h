#pragma once

class Tone
{
public:
  int durationMs;
  int frequencyHz;

  Tone(int frequencyHz, int durationMs);

  Tone(const Tone &other)
      : frequencyHz(other.frequencyHz), durationMs(other.durationMs)
  {
  }
};