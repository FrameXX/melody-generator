#pragma once

class Tone
{
public:
  int startFrequency;
  int endFrequency;
  int durationMs;
  int startVolume;
  int endVolume;

  Tone(int startFrequency,
       int endFrequency,
       int durationMs,
       int startVolume = 50,
       int endVolume = 50);
};