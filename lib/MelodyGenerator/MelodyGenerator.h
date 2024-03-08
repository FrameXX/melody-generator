#pragma once

#include <Pin.h>
#include <Speaker.h>
#include <Ticker.h>
#include <WiFiConnection.h>
#include <NtfyTopicClient.h>
#include <Report.h>
#include <NumberList.h>
#include <Amplify.h>

class MelodyGenerator
{
private:
  Pin volumeSliderPin;
  WiFiConnection wifiConnection;
  Speaker speaker;
  NtfyTopicClient ntfyClient;
  Ticker speakerTicker = Ticker([this]()
                                { this->speaker.keepPlaying(); },
                                2);
  Ticker wifiConnectionTicker = Ticker([this]()
                                       { this->wifiConnection.keepAlive(); },
                                       10000);
  Ticker ntfyClientKeepAliveTicker = Ticker([this]()
                                            { this->ntfyClient.keepAlive(); },
                                            5000);
  Ticker ntfyClientPollingTicker = Ticker([this]()
                                          { this->ntfyClient.pollMessages(); },
                                          200);
  Ticker volumeSliderTicker = Ticker([this]()
                                     { this->updateVolume(); },
                                     100);

  void updateTickers();

  void updateVolume();

  void handleNewMsg(const char *message);

  void onNtfyClientConnected();

public:
  MelodyGenerator(Pin &speakerModulationPin,
                  Pin &volumeSliderPin,
                  String ntfyTopic,
                  const char *wifiSSID,
                  const char *wifiPass);

  void update();
};