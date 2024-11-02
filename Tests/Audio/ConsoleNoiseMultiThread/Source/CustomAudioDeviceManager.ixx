module;

#include <juce_audio_devices.h>

export module CustomAudioDeviceManager;

export
{
    
    /*
    We could have just instanced a normal AudioDeviceManager in main(), but am doing this to setup infastructure
    for any potential, future customizations and follow this programs module convention.
    */


    class CustomAudioDeviceManager : public juce::AudioDeviceManager
    {
    public:
        CustomAudioDeviceManager() {}
        ~CustomAudioDeviceManager() {}
    };
    
}

module : private;