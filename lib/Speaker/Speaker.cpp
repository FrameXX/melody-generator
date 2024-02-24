#include <Speaker.h>

Speaker::Speaker(const Pin &modulationPin, int maxVolume) : modulationPin(modulationPin), maxVolume(maxVolume)
{
  this->modulationPin.useAsOutput();
  this->setVolume(0);
}

Soundwave Speaker::getPlayingSoundwave() const
{
  return this->playingMelody.soundwaves[this->currentSoundwaveIndex];
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

void Speaker::updateSoundwaveFeatures(const Soundwave tone)
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

  const Soundwave playingSoundwave = this->getPlayingSoundwave();
  const unsigned long toneDuration = static_cast<unsigned long>(playingSoundwave.durationMs);
  const bool notPlayingOvertime = this->tonePlayingDuration < toneDuration;
  if (notPlayingOvertime)
  {
    this->updateSoundwaveFeatures(playingSoundwave);
    return;
  }

  const bool playingLastSoundwave = this->currentSoundwaveIndex >= static_cast<int>(this->playingMelody.soundwaves.size()) - 1;
  if (playingLastSoundwave)
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

  this->nextSoundwave();
}

void Speaker::nextSoundwave()
{
  this->currentSoundwaveIndex++;
  const Soundwave newSoundwave = this->getPlayingSoundwave();
  this->playFrequency(newSoundwave.startFrequency);
  this->setVolume(newSoundwave.startVolume);
  this->tonePlayingDuration = 0;
}

void Speaker::restartPlayback()
{
  this->playbackCompleted = false;
  this->currentSoundwaveIndex = 0;
  this->tonePlayingDuration = 0;
  this->updateLastMillis();
  const Soundwave firstSoundwave = this->getPlayingSoundwave();
  this->playFrequency(firstSoundwave.startFrequency);
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