#include <Speaker.h>

Speaker::Speaker(const Pin &modulationPin) : modulationPin(modulationPin)
{
  this->modulationPin.useAsOutput();
  this->modulationPin.modulate(this->volume);
  this->playMelody(this->playingMelody, false);
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
  this->modulationPin.modulate(volume);
}

bool Speaker::shouldRestartPlayback()
{
  if (!this->repeatMelody)
    return false;
  if (this->melodyRepeatCount < this->melodyRepeatedCount && this->melodyRepeatCount != 0)
    return false;
  return true;
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
  if (this->tonePlayingDuration < toneDuration)
  {
    const float tonePortion = (this->tonePlayingDuration * 1000) / toneDuration;
    const int frequencyHz = map(tonePortion, 0, 1000, playingTone.startFrequencyHz, playingTone.endFrequencyHz);
    this->playFrequency(frequencyHz);
    return;
  }

  const bool playingLastTone = this->currentToneIndex >= static_cast<int>(this->playingMelody.tones.size()) - 1;
  if (playingLastTone)
  {
    if (this->shouldRestartPlayback())
    {
      this->melodyRepeatedCount++;
      this->restartPlayback();
      return;
    }
    this->playbackCompleted = true;
    this->playFrequency(0);
    return;
  }

  this->nextTone();
}

void Speaker::nextTone()
{
  this->currentToneIndex++;
  const Tone newTone = this->getPlayingTone();
  this->playFrequency(newTone.startFrequencyHz);
  this->tonePlayingDuration = 0;
}

void Speaker::restartPlayback()
{
  this->playbackCompleted = false;
  this->currentToneIndex = 0;
  this->tonePlayingDuration = 0;
  this->updateLastMillis();
  const Tone firstTone = this->getPlayingTone();
  this->playFrequency(firstTone.startFrequencyHz);
}

void Speaker::playMelody(const Melody &melody, bool repeat, int repeatCount)
{
  this->playingMelody = melody;
  this->repeatMelody = repeat;
  this->melodyRepeatedCount = 0;
  this->melodyRepeatCount = repeatCount;
  this->restartPlayback();
}

void Speaker::playFrequency(int frequency)
{
  if (frequency == 0)
  {
    this->modulationPin.modulate(0);
    return;
  }
  else
  {
    this->modulationPin.modulate(this->volume);
  }
  analogWriteFreq(frequency);
}

void Speaker::keepPlaying()
{
  this->updateMelodyPlayback();
}