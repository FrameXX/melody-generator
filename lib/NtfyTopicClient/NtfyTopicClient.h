#pragma once

#include <Arduino.h>
#include <WiFiConnection.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>

typedef std::function<void()> ConnectedCallback;

class NtfyTopicClient
{
private:
  typedef std::function<void(String)> MsgCallback;
  WiFiConnection wifiConnection;
  WiFiClientSecure wifiClient = WiFiClientSecure();
  websockets::WebsocketsClient websocketClient = websockets::WebsocketsClient();
  MsgCallback messageCallback;
  ConnectedCallback connectedCallback;
  String topic;
  String serverURL;
  bool connected = false;
  bool busy = false;
  bool lastConnectedState = false;

  void
  onNewMessage(websockets::WebsocketsMessage message);

  void setupWifiClient();

  void setupWebsocketClient();

  void postMessage(String message);

  void connect();

  void disconnect();

public:
  NtfyTopicClient(
      const WiFiConnection &wifiConnection,
      String topic,
      const MsgCallback messageCallback,
      const ConnectedCallback connectedCallback = []() {});

  void sendMessage(String message);

  void keepAlive();

  void pollMessages();
};