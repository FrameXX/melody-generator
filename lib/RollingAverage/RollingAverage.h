#pragma once

#include <vector>

template <typename Number>
class RollingAverage
{
private:
  std::vector<Number> values;
  unsigned int capacity;

public:
  RollingAverage(unsigned int capacity) : capacity(capacity)
  {
    values.reserve(capacity);
  }

  Number getAverage()
  {
    Number sum = 0;
    for (Number value : values)
    {
      sum += value;
    }
    return static_cast<Number>(sum) / static_cast<Number>(values.size());
  }

  void addValue(Number value)
  {
    if (values.size() >= capacity)
    {
      values.erase(values.begin());
    }
    values.push_back(value);
  }

  void resize(int newCapacity)
  {
    capacity = newCapacity;
    values.resize(capacity);
  }
};