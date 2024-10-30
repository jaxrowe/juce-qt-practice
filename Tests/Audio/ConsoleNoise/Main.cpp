//--
#include <thread> // For std::this_thread
#include <chrono> // For std::chrono::seconds

//--
import AudioDeviceManager;
import AudioSourcePlayer;
import SourceNoise;

//--
int main (int argc, char* argv[])
{
    Manager.initialiseWithDefaultDevices(0, 2);
    Player.setSource(&sourceNoise);
    Manager.addAudioCallback(&Player);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    Messenger->runDispatchLoop();
    return 0;
}
