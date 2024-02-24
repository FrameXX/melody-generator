#pragma once

#include <Pin.h>
#include <Speaker.h>
#include <Ticker.h>
#include <WiFiConnection.h>
#include <NtfyTopicClient.h>
#include <Report.h>
#include <NumberList.h>

class MelodyGenerator
{
private:
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

  void
  updateTickers();

  void handleNewMsg(const char *message);

  void onNtfyClientConnected();

public:
  MelodyGenerator(Pin &speakerModulationPin, String ntfyTopic, const char *wifiSSID, const char *wifiPass);

  void update();
};