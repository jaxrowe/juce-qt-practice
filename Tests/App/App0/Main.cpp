//--
#include <juce_events.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

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

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Main", "Main");

    return app.exec();
}
