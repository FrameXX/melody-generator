#pragma once

#include <vector>
#include <Soundwave.h>

class Melody
{
public:
  std::vector<Soundwave> soundwaves;

  Melody(std::vector<Soundwave> soundwaves);
};