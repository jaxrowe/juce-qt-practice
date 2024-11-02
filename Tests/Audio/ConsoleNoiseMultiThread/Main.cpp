//--
#include <thread>
#include <chrono>
#include <juce_events.h>
#include <iostream>

//--
import MessengerTrigger;
import CustomAudioDeviceManager;
import AudioSourcePlayer;
import SourceNoise;

//--
int main (int argc, char* argv[])
{
    /*
    Creating a instance of MessengerTrigger will create the MessageManager, and runDispatchLoop() both on its own thread.
    remember, MessageManager must be created before AudioDeviceManager.
    */
    auto triggerHandle = std::make_unique<MessengerTrigger>();
    CustomAudioDeviceManager audioManager;

    /*
    Do the standard audio backend routine
    */
    audioManager.initialiseWithDefaultDevices(0, 2);
    Player.setSource(&sourceNoise);
    audioManager.addAudioCallback(&Player);

    std::cout << "Noise should play for 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    /*
    juce::MessageManager is a Singleton, since we #include <juce_events.h>, we can call it directly from here
    without having to go through triggerHandle, which has the 'Messenger' pointer to the internal instance,
    but it's scoped to the run() method and we couldn't access it without more setup.
    I believe this is a advantage of Single patterns, anyway!

    I have no idea what I'm doing in terms of threading here, I know stopDispatchLoop will cause the thread
    to finish it's execution, and the OS puts it in a terminated state automatically?
    */
    std::cout << "Stopping Messenger Dispatch Loop" << std::endl;
    juce::MessageManager::getInstance()->stopDispatchLoop();

    triggerHandle.reset(); // This should kill the message thead? but the internal MessageManager::instance would still exist..

    std::cout << "At this point, we could deallocate our audio backend for safe shutdown" << std::endl;
    std::cout << "by calling a dedicated shutdownAudioBackend() method. As noted in MessengerTrigger.ixx," << std::endl;
    std::cout << "you would call it before the MessengerTrigger::run() exits." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Bye!" << std::endl;

    return 0;
}
