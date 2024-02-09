#pragma once

class Tone
{
public:
  int startFrequencyHz;
  int endFrequencyHz;
  int durationMs;

  Tone(int startFrequencyHz,
       int endFrequencyHz,
       int durationMs);
};