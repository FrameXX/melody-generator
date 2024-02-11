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
  analogWriteRange(2048);
  this->wifiConnection.getConnected();
  this->speaker.setVolume(100);
  this->speaker.playMelody(Melody(std::vector({Tone(300, 300, 300), Tone(400, 400, 300)})));

  this->speakerTicker.start();
  this->wifiConnectionTicker.start();
  this->ntfyClientKeepAliveTicker.start();
  this->ntfyClientPollingTicker.start();
}

void MelodyGenerator::handleNewMsgCmd(MsgCmd msgCmd)
{
  const int toneArgumentsSize = 5;

  if (msgCmd.arguments.size() < 2 || (msgCmd.arguments.size() - 1) % toneArgumentsSize != 0)
  {
    report("MsgCmd has invalid number of arguments");
    return;
  }

  const bool repeat = msgCmd.commandId;
  const bool repeatCount = msgCmd.arguments[0];
  std::vector<Tone> tones;
  for (unsigned int i = 1; i < msgCmd.arguments.size() - 1; i += toneArgumentsSize)
  {
    const int startFrequency = msgCmd.arguments[i];
    const int endFrequency = msgCmd.arguments[i + 1];
    const int startVolume = msgCmd.arguments[i + 2];
    const int endVolume = msgCmd.arguments[i + 3];
    const int duration = msgCmd.arguments[i + 4];
    const Tone tone(startFrequency, endFrequency, duration, startVolume, endVolume);
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
  this->speaker.playMelody(Melody(std::vector({Tone(400, 400, 300), Tone(300, 300, 300), Tone(400, 400, 300)})));
}

void MelodyGenerator::update()
{
  this->updateTickers();
}