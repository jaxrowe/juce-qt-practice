module;

#include <juce_audio_devices.h>

export module CustomAudioSourcePlayer;

export
{
    class CustomAudioSourcePlayer : public juce::AudioSourcePlayer {};
    
}

module : private;