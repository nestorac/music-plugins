#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_extra/juce_gui_extra.h>

class Mix3DPluginAudioProcessor : public juce::AudioProcessor
{
public:
    Mix3DPluginAudioProcessor();
    ~Mix3DPluginAudioProcessor() override {}

    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* xParam = nullptr;
    std::atomic<float>* yParam = nullptr;
    std::atomic<float>* zParam = nullptr;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mix3DPluginAudioProcessor)
};
