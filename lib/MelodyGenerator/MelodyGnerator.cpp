#include <MelodyGenerator.h>

MelodyGenerator::MelodyGenerator(
    Pin &speakerModulationPin,
    String ntfyTopic,
    const char *wifiSSID,
    const char *wifiPass) : wifiConnection(wifiSSID, wifiPass),
                            speaker(speakerModulationPin),
                            ntfyClient(
                                wifiConnection, ntfyTopic, [this](MsgCmd msgCmd)
                                { this->handleNewMsgCmd(msgCmd); },
                                [this]()
                                { this->onNtfyClientConnected(); })
{
  this->wifiConnection.getConnected();

  this->speakerTicker.start();
  this->wifiConnectionTicker.start();
  this->ntfyClientKeepAliveTicker.start();
  this->ntfyClientPollingTicker.start();
}

void MelodyGenerator::handleNewMsgCmd(MsgCmd msgCmd)
{
  if (msgCmd.arguments.size() < 2 || msgCmd.arguments.size() % 2 == 0)
  {
    report("MsgCmd has invalid number of arguments");
    return;
  }

  const bool repeat = msgCmd.commandId;
  const bool repeatCount = msgCmd.arguments[0];
  std::vector<Tone> tones;
  for (unsigned int i = 1; i < msgCmd.arguments.size() - 1; i += 2)
  {
    const int frequency = msgCmd.arguments[i];
    const int duration = msgCmd.arguments[i + 1];
    const Tone tone(frequency, duration);
    tones.push_back(tone);
  }

  const Melody melody(tones);
  this->speaker.playMelody(melody, repeat, repeatCount);
}

void MelodyGenerator::updateTickers()
{
  this->speakerTicker.update();
  this->wifiConnectionTicker.update();
  this->ntfyClientKeepAliveTicker.update();
  this->ntfyClientPollingTicker.update();
}

void MelodyGenerator::onNtfyClientConnected()
{
  this->speaker.playMelody(Melody(std::vector({Tone(300, 200), Tone(0, 50), Tone(300, 200), Tone(400, 200)})), false);
}

void MelodyGenerator::update()
{
  this->updateTickers();
}