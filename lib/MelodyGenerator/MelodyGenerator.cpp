#include <MelodyGenerator.h>

MelodyGenerator::MelodyGenerator(
    Pin &speakerModulationPin,
    String ntfyTopic,
    const char *wifiSSID,
    const char *wifiPass) : wifiConnection(wifiSSID, wifiPass),
                            speaker(speakerModulationPin),
                            ntfyClient(
                                wifiConnection, ntfyTopic, [this](const char *message)
                                { this->handleNewMsg(message); },
                                [this]()
                                { this->onNtfyClientConnected(); })
{
  analogWriteRange(8192);
  this->wifiConnection.getConnected();
  this->speaker.setVolume(100);
  this->speaker.playMelody(Melody(std::vector({Soundwave(300, 300, 300), Soundwave(400, 400, 300)})));

  this->speakerTicker.start();
  this->wifiConnectionTicker.start();
  this->ntfyClientKeepAliveTicker.start();
  this->ntfyClientPollingTicker.start();
}

void MelodyGenerator::handleNewMsg(const char *message)
{
  const int soundwaveValuesSize = 2;

  reportValue(message, "message");
  const NumberList valuesList = NumberList::fromString(message);
  const unsigned int valuesListSize = valuesList.numbers.size();
  reportValue(valuesListSize, "message values count");

  if (valuesListSize < 2 || (valuesListSize - 1) % soundwaveValuesSize != 0)
  {
    report("message has invalid number of values");
    return;
  }

  const Melody melody = Melody::fromNumberList(soundwaveValuesSize, valuesList);
  const bool repeatCount = valuesList.numbers[0];
  this->speaker.playMelody(melody, repeatCount);
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
  this->speaker.playMelody(Melody(std::vector({Soundwave(400, 400, 300), Soundwave(300, 300, 300), Soundwave(400, 400, 300)})));
}

void MelodyGenerator::update()
{
  this->updateTickers();
}