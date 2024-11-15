//--
#include <juce_events.h>
#include <juce_audio_devices.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
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
