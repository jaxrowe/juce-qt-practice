//--
#include <thread>
#include <chrono>
#include <juce_events.h>

//--
import CustomAudioDeviceManager;
import CustomAudioSourcePlayer;
import SourceNoise;

//--
int main (int argc, char* argv[])
{
    juce::ScopedJuceInitialiser_GUI juceInit;

    CustomAudioDeviceManager Manager;
    CustomAudioSourcePlayer Player;
    SourceNoise sourceNoise;

    Manager.initialiseWithDefaultDevices(0, 2);
    Player.setSource(&sourceNoise);
    Manager.addAudioCallback(&Player);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}
