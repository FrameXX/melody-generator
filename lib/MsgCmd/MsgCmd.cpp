#include <MsgCmd.h>

MsgCmd::MsgCmd(int cmdType, std::vector<int> args) : commandId(cmdType), arguments(args) {}

MsgCmd MsgCmd::fromString(String message)
{
  std::vector<String> argsStr = explode(message, ' ');
  std::vector<int> args;

  for (int i = 0; i < argsStr.size(); i++)
  {
    args.push_back(argsStr[i].toInt());
  }

  const int cmdType = args[0];
  args.erase(args.begin());
  return MsgCmd(cmdType, args);
}

String MsgCmd::toString() const
{
  String result = String(this->commandId);
  for (int arg : this->arguments)
  {
    result += " ";
    result += String(arg);
  }
  return result;
}