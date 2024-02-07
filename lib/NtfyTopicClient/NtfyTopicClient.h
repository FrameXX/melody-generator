#pragma once

#include <Arduino.h>
#include <WiFiConnection.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>

class NtfyTopicClient
{
private:
  typedef std::function<void(String)> MsgCallback;
  WiFiConnection wifiConnection;
  WiFiClientSecure wifiClient = WiFiClientSecure();
  websockets::WebsocketsClient websocketClient = websockets::WebsocketsClient();
  MsgCallback messageCallback;
  String topic;
  String serverURL;
  bool connected = false;
  bool busy = false;

  void
  onNewMessage(websockets::WebsocketsMessage message);

  void setupWifiClient();

  void setupWebsocketClient();

  void postMessage(String message);

  void connect();

  void disconnect();

public:
  NtfyTopicClient(WiFiConnection &wifiConnection, String topic, MsgCallback messageCallback);

  void sendMessage(String message);

  void keepAlive();

  void pollMessages();
};