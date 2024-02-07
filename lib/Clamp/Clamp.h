#pragma once

template <typename Number>
Number clamp(Number value, Number minValue, Number maxValue)
{
  if (value < minValue)
  {
    return minValue;
  }
  else if (value > maxValue)
  {
    return maxValue;
  }
  else
  {
    return value;
  }
}