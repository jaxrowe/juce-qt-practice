module;

#include <juce_audio_devices.h>
#include <juce_events.h>

export module AudioDeviceManager;

export
{
    auto Messenger {juce::MessageManager::getInstance()};
    juce::AudioDeviceManager Manager;
}

module : private;