#include <Melody.h>

Melody::Melody(std::vector<Soundwave> soundwaves) : soundwaves(soundwaves)
{
}

Melody Melody::fromNumberList(int soundwaveValuesSize, const NumberList &numberList, int startGainLinearRampDurationMs, float startGainLinearRampDurationRatio, int maxFinishGainLinearRampDurationMs)
{
  const unsigned int valuesListSize = numberList.numbers.size();
  std::vector<Soundwave> soundwaves;
  for (unsigned int i = 1; i < valuesListSize; i += soundwaveValuesSize)
  {
    const int frequency = numberList.numbers[i];
    const unsigned int totalDurationMs = numberList.numbers[i + 1];

    if (!frequency)
    {
      const Soundwave rest(0, 0, totalDurationMs, 0, 0);
      soundwaves.push_back(rest);
      continue;
    }

    const int soundwaveDurationMs = totalDurationMs - 100;
    const int actualStartGainLinearRampDurationMs = std::min(100 + soundwaveDurationMs, startGainLinearRampDurationMs);
    const Soundwave startGainSoundwave(frequency, frequency, actualStartGainLinearRampDurationMs, 0, 50);
    soundwaves.push_back(startGainSoundwave);

    if (soundwaveDurationMs > 0)
    {
      const Soundwave soundwave(frequency, frequency, soundwaveDurationMs);
      soundwaves.push_back(soundwave);
    }

    if (i + soundwaveValuesSize >= valuesListSize)
      continue;

    const int nextSoundwaveFrequency = numberList.numbers[i + soundwaveValuesSize];
    const bool isNextSoundwaveRest = nextSoundwaveFrequency == 0;

    if (!isNextSoundwaveRest)
      continue;

    const int restDurationMs = numberList.numbers[i + soundwaveValuesSize + 1];
    int finishGainLinearRampDurationMs = static_cast<float>(totalDurationMs) * startGainLinearRampDurationRatio;
    finishGainLinearRampDurationMs = std::min(finishGainLinearRampDurationMs, maxFinishGainLinearRampDurationMs);
    const int actualFinishGainLinearRampDurationMs = std::min(finishGainLinearRampDurationMs, restDurationMs);

    const Soundwave finishGainSoundwave(frequency, frequency, actualFinishGainLinearRampDurationMs, 50, 0);
    soundwaves.push_back(finishGainSoundwave);
  }

  const Melody melody(soundwaves);
  return melody;
}