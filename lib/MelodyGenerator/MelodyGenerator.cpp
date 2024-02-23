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
  this->speaker.playMelody(Melody(std::vector({Tone(300, 300, 300), Tone(400, 400, 300)})));

  this->speakerTicker.start();
  this->wifiConnectionTicker.start();
  this->ntfyClientKeepAliveTicker.start();
  this->ntfyClientPollingTicker.start();
}

void MelodyGenerator::handleNewMsg(const char *message)
{
  const int toneArgumentsSize = 5;

  reportValue(message, "message");
  const NumberList valuesList = NumberList::fromString(message);
  const int valuesListSize = valuesList.numbers.size();
  reportValue(valuesListSize, "message values count");

  if (valuesListSize < 2 || (valuesListSize - 1) % toneArgumentsSize != 0)
  {
    report("message has invalid number of values");
    return;
  }

  const bool repeatCount = valuesList.numbers[0];

  std::vector<Tone> tones;
  for (unsigned int i = 1; i < valuesListSize; i += toneArgumentsSize)
  {
    const int startFrequency = valuesList.numbers[i];
    const int endFrequency = valuesList.numbers[i + 1];
    const int startVolume = valuesList.numbers[i + 2];
    const int endVolume = valuesList.numbers[i + 3];
    const int duration = valuesList.numbers[i + 4];
    const Tone tone(startFrequency, endFrequency, duration, startVolume, endVolume);
    tones.push_back(tone);
  }

  const Melody melody(tones);
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
  this->speaker.playMelody(Melody(std::vector({Tone(400, 400, 300), Tone(300, 300, 300), Tone(400, 400, 300)})));
}

void MelodyGenerator::update()
{
  this->updateTickers();
}