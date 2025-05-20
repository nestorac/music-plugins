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
    auto inSet  = layouts.getMainInputChannelSet();
    auto outSet = layouts.getMainOutputChannelSet();

    // allow mono→stereo and stereo→stereo only
    return (outSet == juce::AudioChannelSet::stereo())
        && (inSet == juce::AudioChannelSet::mono() 
         || inSet == juce::AudioChannelSet::stereo());
}

void Mix3DPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto numCh   = buffer.getNumChannels();
    auto numSamp = buffer.getNumSamples();
    float x      = *xParam;

    // you can still pan a summed signal, or pan each channel differently—
    // here we’ll pan the summed mono to stereo, then add the original stereo on top:
    auto* in0 = buffer.getReadPointer (0);
    auto* in1 = buffer.getNumChannels() > 1
                   ? buffer.getReadPointer (1)
                   : buffer.getReadPointer (0);

    auto* out0 = buffer.getWritePointer (0);
    auto* out1 = buffer.getWritePointer (1);

    for (int i = 0; i < numSamp; ++i)
    {
        float monoIn = 0.5f * (in0[i] + in1[i]);
        float gainL  = 0.5f * (1.0f - x);
        float gainR  = 0.5f * (1.0f + x);

        // clear buffers (if you want pure panning)
        out0[i] = monoIn * gainL;
        out1[i] = monoIn * gainR;

        // —or— add to the original stereo:
        // out0[i] = in0[i] + monoIn * gainL;
        // out1[i] = in1[i] + monoIn * gainR;
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
