#include "Noise.h"

void Noise::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    /* 

    This function will be called when the audio device is started, or when
    its settings (i.e. sample rate, block size, etc) are changed.

    You can use this function to initialise any resources you might need,
    but be careful - it will be called on the audio thread, not the GUI thread.

    For more details, see the help for AudioProcessor::prepareToPlay()

    samplesPerBlockExpected and sampleRate came from AudioSource, which this class inherits from
    thus created when this class is instantiated

    You would never want to actually print here, in the Audio thread.
    */
   
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog (message);
}

void Noise::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // for the number of channels defined in the 'buffer' object inside AudioSourceChannelInfo
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        //  fetch a writable pointer of one of 'buffers' channel
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (int sample = 0; sample < bufferToFill.numSamples; ++ sample)
            {
            buffer[sample] = (random.nextFloat() * 2.0f - 1.0f) * 0.1f;
            }
    }
}

void Noise::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}
