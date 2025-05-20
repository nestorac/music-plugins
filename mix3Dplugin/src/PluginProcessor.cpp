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

    // allow mono→stereo and stereo to stereo only
    return (outSet == juce::AudioChannelSet::stereo())
        && (inSet == juce::AudioChannelSet::mono() 
         || inSet == juce::AudioChannelSet::stereo());
}

void Mix3DPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int numCh   = buffer.getNumChannels();
    const int numSamp = buffer.getNumSamples();

    float x = *xParam;
    float z = *zParam;

    // Mapeamos z ∈ [–1,1] a depthGain ∈ [1,0]:
    //  z = –1 → depthGain = 1 (muy cerca / delante)
    //  z = +1 → depthGain = 0 (muy lejos / atrás)
    float depthGain = juce::jmap(z, -1.0f, 1.0f, 1.0f, 0.0f);

    // Lectura de input (mono):
    auto* in0 = buffer.getReadPointer (0);
    auto* in1 = (numCh > 1) ? buffer.getReadPointer (1)
                            : buffer.getReadPointer (0);

    auto* outL = buffer.getWritePointer (0);
    auto* outR = buffer.getWritePointer (1);

    for (int i = 0; i < numSamp; ++i)
    {
        // Mezcla mono de ambas entradas
        float inMono = 0.5f * (in0[i] + in1[i]);

        // Pan lateral
        float gainL = 0.5f * (1.0f - x);
        float gainR = 0.5f * (1.0f + x);

        // Aplica profundidad
        outL[i] = inMono * gainL * depthGain;
        outR[i] = inMono * gainR * depthGain;
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
