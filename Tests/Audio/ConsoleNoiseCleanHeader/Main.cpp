//--
#include <thread>
#include <chrono>
#include <juce_events.h>
#include <juce_audio_devices.h>
#include "Noise.h"

//--
int main (int argc, char* argv[])
{
    juce::ScopedJuceInitialiser_GUI juceInit;

    juce::AudioDeviceManager Manager;
    juce::AudioSourcePlayer Player;
    Noise noise;

    Manager.initialiseWithDefaultDevices(0, 2);
    Player.setSource(&noise);
    Manager.addAudioCallback(&Player);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}
