module;

#include <juce_audio_devices.h>

export module CustomAudioDeviceManager;

export
{
    class CustomAudioDeviceManager : public juce::AudioDeviceManager {};
}

module : private;