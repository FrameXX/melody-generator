#pragma once

#include <ESP8266WiFi.h>
#include <Report.h>

class WiFiConnection
{
private:
  const char *SSID;
  const char *password;

  void connect();

public:
  WiFiConnection(const char *SSID, const char *password);

  bool getConnected();

  void keepAlive();
};