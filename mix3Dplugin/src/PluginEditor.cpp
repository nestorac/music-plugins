#include "PluginEditor.h"

Mix3DPluginAudioProcessorEditor::Mix3DPluginAudioProcessorEditor (Mix3DPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(xSlider);
    xSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    xSlider.setRange(-1.0, 1.0);
    xSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    xAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "x", xSlider);

    setSize (400, 300);
}

void Mix3DPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Mix 3D Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void Mix3DPluginAudioProcessorEditor::resized()
{
    xSlider.setBounds (40, 80, getWidth() - 80, 20);
}
