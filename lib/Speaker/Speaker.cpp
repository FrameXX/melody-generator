#include <Speaker.h>

Speaker::Speaker(const Pin &modulationPin, int maxVolume) : modulationPin(modulationPin), maxVolume(maxVolume)
{
  this->modulationPin.useAsOutput();
  this->setVolume(0);
}

Tone Speaker::getPlayingTone() const
{
  return this->playingMelody.tones[this->currentToneIndex];
}

void Speaker::updateLastMillis()
{
  this->lastMillis = millis();
}

void Speaker::setVolume(int volume)
{
  volume = clamp(volume, 0, 100);
  volume = amplify(volume, 0, 100, 2);
  volume = map(volume, 0, 100, 0, this->maxVolume);
  this->modulationPin.modulate(volume);
}

bool Speaker::shouldRestartPlayback()
{
  if (this->melodyRepeatCount == 0)
    return true;
  if (this->melodyRepeatCount <= this->melodyRepeatedCount)
    return false;
  return true;
}

void Speaker::updateToneFeatures(const Tone tone)
{
  const unsigned long toneDuration = static_cast<unsigned long>(tone.durationMs);
  const float tonePortion = (this->tonePlayingDuration * 1000) / toneDuration;

  const int frequency = map(tonePortion, 0, 1000, tone.startFrequency, tone.endFrequency);
  this->playFrequency(frequency);
  const int volume = map(tonePortion, 0, 1000, tone.startVolume, tone.endVolume);
  this->setVolume(volume);
}

void Speaker::updateMelodyPlayback()
{
  if (this->playbackCompleted)
    return;

  const unsigned long millisDiff = millis() - this->lastMillis;
  this->tonePlayingDuration += millisDiff;
  this->updateLastMillis();

  const Tone playingTone = this->getPlayingTone();
  const unsigned long toneDuration = static_cast<unsigned long>(playingTone.durationMs);
  const bool notPlayingOvertime = this->tonePlayingDuration < toneDuration;
  if (notPlayingOvertime)
  {
    this->updateToneFeatures(playingTone);
    return;
  }

  const bool playingLastTone = this->currentToneIndex >= static_cast<int>(this->playingMelody.tones.size()) - 1;
  if (playingLastTone)
  {
    this->melodyRepeatedCount++;
    if (this->shouldRestartPlayback())
    {
      this->restartPlayback();
      return;
    }
    this->playbackCompleted = true;
    this->setVolume(0);
    return;
  }

  this->nextTone();
}

void Speaker::nextTone()
{
  this->currentToneIndex++;
  const Tone newTone = this->getPlayingTone();
  this->playFrequency(newTone.startFrequency);
  this->setVolume(newTone.startVolume);
  this->tonePlayingDuration = 0;
}

void Speaker::restartPlayback()
{
  this->playbackCompleted = false;
  this->currentToneIndex = 0;
  this->tonePlayingDuration = 0;
  this->updateLastMillis();
  const Tone firstTone = this->getPlayingTone();
  this->playFrequency(firstTone.startFrequency);
}

void Speaker::playMelody(const Melody &melody, int repeatCount)
{
  this->playingMelody = melody;
  this->melodyRepeatedCount = 0;
  this->melodyRepeatCount = repeatCount;
  this->restartPlayback();
}

void Speaker::playFrequency(int frequency)
{
  frequency = clamp(frequency, 1, 3000);
  analogWriteFreq(frequency);
}

void Speaker::keepPlaying()
{
  this->updateMelodyPlayback();
}