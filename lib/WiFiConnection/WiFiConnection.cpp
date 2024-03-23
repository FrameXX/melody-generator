#include <WiFiConnection.h>

WiFiConnection::WiFiConnection(const char *SSID, const char *password, int connectionTimeoutMs) : SSID(SSID), password(password), connectionTimeoutMs(connectionTimeoutMs)
{
  this->connect();
}

void WiFiConnection::connect()
{
  if (connecting && (millis() - this->lastConnectionTimeMs <= this->connectionTimeoutMs))
    return;
  report("trying to connect to wifi");
  this->connecting = true;
  this->lastConnectionTimeMs = millis();
  WiFi.begin(this->SSID, this->password);
}

bool WiFiConnection::getConnected()
{
  const bool connected = WiFi.status() == wl_status_t::WL_CONNECTED;
  return connected;
}

void WiFiConnection::keepAlive()
{
  const bool connected = this->getConnected();
  reportValue(connected, "wifi connection state");
  if (connected)
    return;
  this->connect();
}