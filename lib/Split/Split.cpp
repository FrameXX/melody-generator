#include <Split.h>

std::vector<int> split(const char *str, char delimiter)
{
  std::vector<int> tokens;
  char *token = strtok((char *)str, &delimiter);
  while (token != NULL)
  {
    tokens.push_back(atoi(token));
    token = strtok(NULL, &delimiter);
  }
  return tokens;
}