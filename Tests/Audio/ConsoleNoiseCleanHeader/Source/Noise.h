#pragma once

#include <juce_audio_basics.h>
#include <juce_core.h>

class Noise : public juce::AudioSource
{
public:

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    void releaseResources() override;

private:
    juce::Random random;

};

