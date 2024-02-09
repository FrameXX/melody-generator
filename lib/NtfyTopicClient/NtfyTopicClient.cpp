#include <NtfyTopicClient.h>

NtfyTopicClient::NtfyTopicClient(const WiFiConnection &wifiConnection,
                                 String topic,
                                 const MsgCallback messageCallback,
                                 ConnectedCallback connectedCallback) : wifiConnection(wifiConnection),
                                                                        messageCallback(messageCallback),
                                                                        topic(topic),
                                                                        serverURL("wss://ntfy.sh/" + topic + "/ws"),
                                                                        connectedCallback(connectedCallback)
{
  this->setupWifiClient();
  this->setupWebsocketClient();
}

void NtfyTopicClient::connect()
{
  report("trying to connect to channel");
  if (!this->wifiConnection.getConnected())
    return;
  this->connected = this->websocketClient.connect(this->serverURL);
}

void NtfyTopicClient::disconnect()
{
  report("disconnecting from channel");
  this->websocketClient.close();
  this->connected = false;
}

void NtfyTopicClient::setupWifiClient()
{
  this->wifiClient.setInsecure();
}

void NtfyTopicClient::setupWebsocketClient()
{
  this->websocketClient.setInsecure();
  this->websocketClient.onMessage([this](const websockets::WebsocketsMessage &message)
                                  { this->onNewMessage(message); });
}

void NtfyTopicClient::onNewMessage(websockets::WebsocketsMessage message)
{
  JsonDocument document;
  deserializeJson(document, message.data());
  if (document["event"] != "message")
    return;
  this->messageCallback(document["message"]);
}

void NtfyTopicClient::postMessage(String message)
{
  if (!this->wifiClient.connect("ntfy.sh", 443))
    return;
  String request = "POST /" + this->topic + " HTTP/1.1\r\n" + "Host: " + "ntfy.sh" + "\r\n" + "Content-Type: text/plain\r\n" + "Content-Length: " + String(message.length()) + "\r\n" + "Connection: close\r\n" + "\r\n" + message + "\r\n";
  this->wifiClient.print(request);
  this->wifiClient.stop();
}

void NtfyTopicClient::sendMessage(String message)
{
  report("sending message");
  reportValue(message, "message");
  if (!this->wifiConnection.getConnected())
    return;
  this->busy = true;
  this->disconnect();
  this->postMessage(message);
  this->connect();
  this->busy = false;
}

void NtfyTopicClient::keepAlive()
{
  const bool connected = this->connected;
  if (this->lastConnectedState != this->connected && connected)
    this->connectedCallback();
  this->lastConnectedState = connected;

  reportValue(connected, "channel connection state");
  if (!this->connected && !this->busy && this->wifiConnection.getConnected())
    this->connect();
}

void NtfyTopicClient::pollMessages()
{
  this->websocketClient.poll();
}