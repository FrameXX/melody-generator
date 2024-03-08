#pragma once

#include <vector>
#include <Soundwave.h>
#include <NumberList.h>
#include <Report.h>

class Melody
{
public:
  std::vector<Soundwave> soundwaves;

  Melody(std::vector<Soundwave> soundwaves);

  static Melody fromNumberList(int soundwaveValuesSize, const NumberList &numberList, int startGainLinearRampDurationMs = 125, float gainLinearRampDurationRatio = 0.7, int maxFinishGainLinearRampDurationMs = 1000);
};