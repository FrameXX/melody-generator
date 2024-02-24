#pragma once

class Soundwave
{
public:
  int startFrequency;
  int endFrequency;
  int durationMs;
  int startVolume;
  int endVolume;

  Soundwave(int startFrequency,
            int endFrequency,
            int durationMs,
            int startVolume = 50,
            int endVolume = 50);
};