#include <Tone.h>

Tone::Tone(int startFrequencyHz,
           int endFrequencyHz,
           int durationMs) : startFrequencyHz(startFrequencyHz),
                             endFrequencyHz(endFrequencyHz),
                             durationMs(durationMs)
{
}