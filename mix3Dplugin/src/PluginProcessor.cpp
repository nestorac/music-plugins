#include "PluginProcessor.h"
#include "PluginEditor.h"

Mix3DPluginAudioProcessor::Mix3DPluginAudioProcessor()
: parameters(*this, nullptr, juce::Identifier("Params"),
{
    std::make_unique<juce::AudioParameterFloat>("x", "X", -1.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("y", "Y", -1.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("z", "Z", -1.0f, 1.0f, 0.0f)
})
{
    xParam = parameters.getRawParameterValue("x");
    yParam = parameters.getRawParameterValue("y");
    zParam = parameters.getRawParameterValue("z");
}

bool Mix3DPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannels() > 0 && layouts.getMainOutputChannels() == 2;
}

void Mix3DPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    float x = *xParam;

    if (buffer.getNumChannels() < 2)
        return;

    auto* input = buffer.getReadPointer(0);
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float gainL = 0.5f * (1.0f - x);
        float gainR = 0.5f * (1.0f + x);

        left[i]  = input[i] * gainL;
        right[i] = input[i] * gainR;
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Mix3DPluginAudioProcessor();
}

juce::AudioProcessorEditor* Mix3DPluginAudioProcessor::createEditor()
{
    // return your editor, passing *this to its constructor:
    return new Mix3DPluginAudioProcessorEditor (*this);
}
