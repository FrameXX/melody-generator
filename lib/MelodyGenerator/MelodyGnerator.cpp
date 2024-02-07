#include <MelodyGenerator.h>

MelodyGenerator::MelodyGenerator(
    Pin &speakerModulationPin,
    String ntfyTopic,
    const char *wifiSSID,
    const char *wifiPass) : wifiConnection(wifiSSID, wifiPass),
                            speaker(speakerModulationPin),
                            ntfyClient(wifiConnection, ntfyTopic, [this](MsgCmd msgCmd)
                                       { this->handleNewMsgCmd(msgCmd); })
{
  this->wifiConnection.getConnected();

  this->speakerTicker.start();
  this->wifiConnectionTicker.start();
  this->ntfyClientKeepAliveTicker.start();
  this->ntfyClientPollingTicker.start();
}

void MelodyGenerator::handleNewMsgCmd(MsgCmd msgCmd)
{
  reportValue(msgCmd.toString());
}

void MelodyGenerator::updateTickers()
{
  this->speakerTicker.update();
  this->wifiConnectionTicker.update();
  this->ntfyClientKeepAliveTicker.update();
  this->ntfyClientPollingTicker.update();
}

void MelodyGenerator::update()
{
  this->updateTickers();
}