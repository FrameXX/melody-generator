#pragma once

#include <Arduino.h>
#include <Pin.h>
#include <Melody.h>
#include <Report.h>

class Speaker
{
private:
  Pin modulationPin;
  Melody playingMelody = Melody(std::vector({Tone(300, 300, 300), Tone(400, 400, 300)}));
  int currentToneIndex = 0;
  unsigned long tonePlayingDuration = 0;
  unsigned long lastMillis = 0;
  bool repeatMelody = false;
  int melodyRepeatCount = 0;
  int melodyRepeatedCount = 0;
  int volume = 1;
  bool playbackCompleted = false;

  Tone getPlayingTone() const;

  void updateLastMillis();

  void setVolume(int volume);

  void playFrequency(int frequency);

  void updateMelodyPlayback();

  void nextTone();

  bool shouldRestartPlayback();

public:
  Speaker(const Pin &modulationPin);

  void restartPlayback();

  void playMelody(const Melody &melody, bool repeat = true, int repeatCount = 0);

  void keepPlaying();
};