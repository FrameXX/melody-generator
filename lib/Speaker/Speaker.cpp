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

void Speaker::updateMelodyPlayback()
{
  if (this->playbackCompleted)
    return;
  const unsigned long millisDiff = millis() - this->lastMillis;
  this->tonePlayingDuration += millisDiff;
  this->updateLastMillis();

  const Tone playingTone = this->getPlayingTone();
  if (this->tonePlayingDuration < static_cast<unsigned long>(playingTone.durationMs))
    return;

  if (this->currentToneIndex >= static_cast<int>(this->playingMelody.tones.size()) - 1)
  {
    if (!this->repeatMelody)
    {
      this->playbackCompleted = true;
      this->playFrequency(0);
      return;
    }
    if (this->melodyRepeatCount < this->melodyRepeatedCount && melodyRepeatCount != 0)
    {
      this->playbackCompleted = true;
      this->playFrequency(0);
      return;
    }
    this->melodyRepeatedCount++;
    this->restartPlayback();
    return;
  }

  this->nextTone();
}

void Speaker::nextTone()
{
  this->currentToneIndex++;
  const Tone newTone = this->getPlayingTone();
  this->playFrequency(newTone.frequencyHz);
  this->tonePlayingDuration = 0;
}

void Speaker::restartPlayback()
{
  this->playbackCompleted = false;
  this->currentToneIndex = 0;
  this->tonePlayingDuration = 0;
  this->updateLastMillis();
  const Tone firstTone = this->getPlayingTone();
  this->playFrequency(firstTone.frequencyHz);
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