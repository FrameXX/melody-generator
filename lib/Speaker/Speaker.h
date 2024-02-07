#pragma once

#include <Arduino.h>
#include <Pin.h>
#include <Melody.h>

class Speaker
{
private:
  Pin modulationPin;

  void setVolume(int volume);

  void setFrequency(int frequency);

public:
  Speaker(Pin &modulationPin);

  void startPlaying(Melody melody);

  void keepPlaying();
};