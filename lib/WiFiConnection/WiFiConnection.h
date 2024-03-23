#pragma once

#include <ESP8266WiFi.h>
#include <Report.h>

class WiFiConnection
{
private:
  const char *SSID;
  const char *password;
  int lastConnectionTimeMs;
  int connectionTimeoutMs;
  bool connecting = false;

  void connect();

public:
  WiFiConnection(const char *SSID, const char *password, int connectionTimeoutMs = 20000);

  bool getConnected();

  void keepAlive();
};