#pragma once

#include <Arduino.h>
#include <Clamp.h>

class Pin
{
private:
  uint8_t target;

public:
  Pin(uint8_t target);

  void changeTarget(uint8_t target);

  void useAsOutput();

  void useAsInput();

  int readAnalog();

  int readDigital();

  void writeHigh();

  void writeLow();

  void modulate(int dutyFactor);
};