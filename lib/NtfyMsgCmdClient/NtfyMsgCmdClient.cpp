#include <NtfyMsgCmdClient.h>

NtfyMsgCmdClient::NtfyMsgCmdClient(WiFiConnection &wifiConnection,
                                   String topic,
                                   MsgCmdCallback msgCmdCallback,
                                   ConnectedCallback connectedCallback) : topicClient(
                                                                              wifiConnection,
                                                                              topic,
                                                                              [this](String msg)
                                                                              { this->handleNewMsg(msg); },
                                                                              [this]()
                                                                              { this->onConnect(); }),
                                                                          msgCmdCallback(msgCmdCallback),
                                                                          connectedCallback(connectedCallback)
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

void NtfyMsgCmdClient::onConnect()
{
  this->connectedCallback();
}