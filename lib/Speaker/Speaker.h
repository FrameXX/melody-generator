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
  Melody playingMelody = Melody(std::vector({Tone(300, 300, 300), Tone(400, 400, 300)}));
  int currentToneIndex = 0;
  unsigned long tonePlayingDuration = 0;
  unsigned long lastMillis = 0;
  int melodyRepeatCount = 0;
  int melodyRepeatedCount = 0;

  Tone getPlayingTone() const;

  void updateLastMillis();

  void updateMelodyPlayback();

  void nextTone();

  bool shouldRestartPlayback();

  void updateToneFeatures(const Tone tone);

public:
  bool playbackCompleted = true;
  int maxVolume;

  Speaker(const Pin &modulationPin, int maxVolume = 400);

  void setVolume(int volume);

  void playFrequency(int frequency);

  void restartPlayback();

  void playMelody(const Melody &melody, int repeatCount = 1);

  void keepPlaying();
};