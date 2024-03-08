#pragma once

#include <Arduino.h>
#include <Pin.h>
#include <Melody.h>
#include <Report.h>
#include <Clamp.h>
#include <Amplify.h>

class Speaker
{
private:
  Pin modulationPin;
  Melody playingMelody = Melody(std::vector({Soundwave(300, 300, 300), Soundwave(400, 400, 300)}));
  int currentSoundwaveIndex = 0;
  unsigned long soundwavePlayingDuration = 0;
  unsigned long lastMillis = 0;
  int melodyRepeatCount = 0;
  int melodyRepeatedCount = 0;
  int volume = 0;

  Soundwave getPlayingSoundwave() const;

  void updateLastMillis();

  void updateMelodyPlayback();

  void nextSoundwave();

  void updateDutyCycle();

  bool shouldRestartPlayback();

  void updateSoundwaveFeatures(const Soundwave soundwave);

  void mute();

public:
  bool playbackCompleted = true;
  int maxVolumeDutyCycle;

  Speaker(const Pin &modulationPin, int maxVolumeDutyCycle = 400);

  void setMaxVolumeDutyCycle(int dutyCycle);

  void setVolume(int volume);

  void playFrequency(int frequency);

  void restartPlayback();

  void playMelody(const Melody &melody, int repeatCount = 1);

  void keepPlaying();
};