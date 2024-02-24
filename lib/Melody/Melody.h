#pragma once

#include <vector>
#include <Soundwave.h>

class Melody
{
public:
  std::vector<Soundwave> tones;

  Melody(std::vector<Soundwave> tones);
};