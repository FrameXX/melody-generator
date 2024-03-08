#include <Arduino.h>
#include <Report.h>
#include <Pin.h>
#include <MelodyGenerator.h>
#include <WiFiCredentials.h>

#define DEBUG true

void setup()
{
  initSerial();
  if (DEBUG)
  {
    report("serial initiated");
    report("waiting 3000ms");
    delay(3000);
  }
  report("init start");

  Pin speakerModulationPin(14);
  Pin volumeSliderPin(A0);

  MelodyGenerator generator(speakerModulationPin, volumeSliderPin, "melody-generator", WIFI_SSID, WIFI_PASS);

  while (true)
  {
    delay(2);
    generator.update();
  }
}

void loop()
{
}