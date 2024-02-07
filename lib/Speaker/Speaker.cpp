#include <Speaker.h>
#include <Pin.h>
#include <Melody.h>

Speaker::Speaker(Pin &modulationPin) : modulationPin(modulationPin)
{
  this->modulationPin.useAsOutput();
  this->setVolume(1);
  this->setFrequency(200);
}

void Speaker::setVolume(int volume)
{
  this->modulationPin.modulate(volume);
}

void Speaker::setFrequency(int frequency)
{
  analogWriteFreq(frequency);
}

void Speaker::startPlaying(Melody melody)
{
}

void Speaker::keepPlaying()
{
}