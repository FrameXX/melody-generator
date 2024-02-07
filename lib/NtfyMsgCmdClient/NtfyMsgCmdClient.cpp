#include <NtfyMsgCmdClient.h>

NtfyMsgCmdClient::NtfyMsgCmdClient(WiFiConnection &wifiConnection,
                                   String topic,
                                   MsgCmdCallback msgCmdCallback) : topicClient(wifiConnection,
                                                                                topic,
                                                                                [this](String msg)
                                                                                { this->handleNewMsg(msg); }),
                                                                    msgCmdCallback(msgCmdCallback)
{
}

void NtfyMsgCmdClient::handleNewMsg(String msg)
{
  MsgCmd msgCmd = MsgCmd::fromString(msg);
  this->msgCmdCallback(msgCmd);
}

void NtfyMsgCmdClient::sendMsgCmd(MsgCmd msgCmd)
{
  const String msg = msgCmd.toString();
  this->topicClient.sendMessage(msg);
}

void NtfyMsgCmdClient::pollMsgCmd()
{
  this->topicClient.pollMessages();
}

void NtfyMsgCmdClient::keepAlive()
{
  this->topicClient.keepAlive();
}