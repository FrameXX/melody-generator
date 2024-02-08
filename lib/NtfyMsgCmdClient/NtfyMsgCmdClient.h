#pragma once

#include <Arduino.h>
#include <NtfyTopicClient.h>
#include <WiFiConnection.h>
#include <MsgCmd.h>

class NtfyMsgCmdClient
{
private:
  typedef std::function<void(MsgCmd)> MsgCmdCallback;
  NtfyTopicClient topicClient;
  MsgCmdCallback msgCmdCallback;
  ConnectedCallback connectedCallback;

  void handleNewMsg(String msg);

public:
  NtfyMsgCmdClient(
      WiFiConnection &wifiConnection, String topic, MsgCmdCallback msgCmdCallback, ConnectedCallback connectedCallback = []() {});

  void sendMsgCmd(MsgCmd msgCmd);

  void pollMsgCmd();

  void keepAlive();

  void onConnect();
};