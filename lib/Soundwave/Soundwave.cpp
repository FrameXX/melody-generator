#include <Soundwave.h>

Soundwave::Soundwave(int startFrequency,
           int endFrequency,
           int durationMs,
           int startVolume,
           int endVolume) : startFrequency(startFrequency),
                            endFrequency(endFrequency),
                            durationMs(durationMs),
                            startVolume(startVolume),
                            endVolume(endVolume)
{
}