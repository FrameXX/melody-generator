#include <NumberList.h>

NumberList::NumberList(const std::vector<int> &numbers) : numbers(numbers) {}

NumberList NumberList::fromString(const char *str)
{
  std::vector<int> numbers;
  char *token = strtok((char *)str, " ");
  while (token != NULL)
  {
    numbers.push_back(atoi(token));
    token = strtok(NULL, " ");
  }
  return NumberList(numbers);
}

std::string NumberList::toString() const
{
  std::stringstream ss;
  for (size_t i = 0; i < numbers.size(); i++)
  {
    if (i > 0)
    {
      ss << ' ';
    }
    ss << numbers[i];
  }
  return ss.str();
}