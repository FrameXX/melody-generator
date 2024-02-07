#pragma once

#include <vector>
#include <Arduino.h>
#include <Report.h>
#include <Explode.h>

class MsgCmd
{
public:
  int commandId;
  std::vector<int> arguments;

  MsgCmd(int cmdType, std::vector<int> args);

  static MsgCmd fromString(String message);

  String toString() const;
};
