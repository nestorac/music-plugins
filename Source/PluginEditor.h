#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "PluginProcessor.h"

class Mix3DPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    Mix3DPluginAudioProcessorEditor (Mix3DPluginAudioProcessor&);
    ~Mix3DPluginAudioProcessorEditor() override {}

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Mix3DPluginAudioProcessor& processor;
    juce::Slider xSlider, ySlider, zSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> xAttachment, yAttachment, zAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mix3DPluginAudioProcessorEditor)
};
