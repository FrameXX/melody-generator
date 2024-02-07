#include <WiFiConnection.h>

WiFiConnection::WiFiConnection(const char *SSID, const char *password) : SSID(SSID), password(password)
{
  this->connect();
}

void WiFiConnection::connect()
{
  report("trying to connect to wifi");
  delay(1000);
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