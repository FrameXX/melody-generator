#include <Speaker.h>

Speaker::Speaker(const Pin &modulationPin, int maxVolumeDutyCycle) : modulationPin(modulationPin), maxVolumeDutyCycle(maxVolumeDutyCycle)
{
  analogWriteRange(8192);
  this->modulationPin.useAsOutput();
  this->updateDutyCycle();
}

Soundwave Speaker::getPlayingSoundwave() const
{
  return this->playingMelody.soundwaves[this->currentSoundwaveIndex];
}

void Speaker::updateLastMillis()
{
  this->lastMillis = millis();
}

void Speaker::updateDutyCycle()
{
  const int dutyCycle = map(this->volume, 0, 100, 0, this->maxVolumeDutyCycle);
  this->modulationPin.modulate(dutyCycle);
}

void Speaker::setVolume(int volume)
{
  volume = clamp(volume, 0, 100);
  volume = amplify(volume, 0, 100, 2);
  this->volume = map(volume, 0, 100, 0, this->maxVolumeDutyCycle);
  this->updateDutyCycle();
}

void Speaker::setMaxVolumeDutyCycle(int dutyCycle)
{
  this->maxVolumeDutyCycle = clamp(dutyCycle, 0, 8192);
  this->updateDutyCycle();
}

bool Speaker::shouldRestartPlayback()
{
  if (this->melodyRepeatCount == 0)
    return true;
  if (this->melodyRepeatCount <= this->melodyRepeatedCount)
    return false;
  return true;
}

void Speaker::updateSoundwaveFeatures(const Soundwave soundwave)
{
  const unsigned long soundwaveDuration = static_cast<unsigned long>(soundwave.durationMs);
  const float soundwavePortion = (this->soundwavePlayingDuration * 1000) / soundwaveDuration;

  const int frequency = map(soundwavePortion, 0, 1000, soundwave.startFrequency, soundwave.endFrequency);
  this->playFrequency(frequency);
  const int volume = map(soundwavePortion, 0, 1000, soundwave.startVolume, soundwave.endVolume);
  this->setVolume(volume);
}

void Speaker::mute()
{
  this->setVolume(0);
}

void Speaker::updateMelodyPlayback()
{
  if (this->playbackCompleted)
    return;

  const unsigned long millisDiff = millis() - this->lastMillis;
  this->soundwavePlayingDuration += millisDiff;
  this->updateLastMillis();

  const Soundwave playingSoundwave = this->getPlayingSoundwave();
  const unsigned long soundwaveDuration = static_cast<unsigned long>(playingSoundwave.durationMs);
  const bool notPlayingOvertime = this->soundwavePlayingDuration < soundwaveDuration;
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
    this->mute();
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
  this->soundwavePlayingDuration = 0;
}

void Speaker::restartPlayback()
{
  this->playbackCompleted = false;
  this->currentSoundwaveIndex = 0;
  this->soundwavePlayingDuration = 0;
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