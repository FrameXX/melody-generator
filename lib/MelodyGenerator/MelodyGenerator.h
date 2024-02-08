#pragma once

#include <Pin.h>
#include <Speaker.h>
#include <Ticker.h>
#include <WiFiConnection.h>
#include <NtfyMsgCmdClient.h>
#include <Report.h>

class MelodyGenerator
{
private:
  WiFiConnection wifiConnection;
  Speaker speaker;
  NtfyMsgCmdClient ntfyClient;
  Ticker speakerTicker = Ticker([this]()
                                { this->speaker.keepPlaying(); },
                                10);
  Ticker wifiConnectionTicker = Ticker([this]()
                                       { this->wifiConnection.keepAlive(); },
                                       8000);
  Ticker ntfyClientKeepAliveTicker = Ticker([this]()
                                            { this->ntfyClient.keepAlive(); },
                                            5000);
  Ticker ntfyClientPollingTicker = Ticker([this]()
                                          { this->ntfyClient.pollMsgCmd(); },
                                          200);

  void
  updateTickers();

  void handleNewMsgCmd(MsgCmd msgCmd);

  void onNtfyClientConnected();

public:
  MelodyGenerator(Pin &speakerModulationPin, String ntfyTopic, const char *wifiSSID, const char *wifiPass);

  void update();
};