#pragma once

#include <vector>
#include <Tone.h>

class Melody
{
public:
  std::vector<Tone> tones;

  Melody(std::vector<Tone> tones);
};