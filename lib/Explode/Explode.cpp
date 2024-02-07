#include <Explode.h>

std::vector<String> explode(const String &str, char delimiter)
{
  std::vector<String> tokens;
  int prevIndex = 0;
  int index = str.indexOf(delimiter);
  while (index != -1)
  {
    tokens.push_back(str.substring(prevIndex, index));
    prevIndex = index + 1;
    index = str.indexOf(delimiter, prevIndex);
  }
  tokens.push_back(str.substring(prevIndex));
  return tokens;
}