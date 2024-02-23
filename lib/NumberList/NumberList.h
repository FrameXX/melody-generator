#pragma once

#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <sstream>

class NumberList
{
public:
  std::vector<int> numbers;

  NumberList(const std::vector<int> &numbers);

  static NumberList fromString(const char *str);

  std::string toString() const;
};