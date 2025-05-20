#include "PluginEditor.h"

Mix3DPluginAudioProcessorEditor::Mix3DPluginAudioProcessorEditor (Mix3DPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // **** SLIDER X ****
    addAndMakeVisible (xSlider);
    xSlider.setSliderStyle (juce::Slider::Rotary);
    xSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    xAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                   processor.parameters, "x", xSlider);

    // **** SLIDER Z ****
    addAndMakeVisible (zSlider);
    zSlider.setSliderStyle (juce::Slider::Rotary);
    zSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    zAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                   processor.parameters, "z", zSlider);

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
    auto area = getLocalBounds().reduced (20);

    // coloca X y Z lado a lado
    auto row = area.removeFromTop (area.getHeight() / 2);
    xSlider.setBounds  (row.removeFromLeft (row.getWidth() / 2).reduced (10));
    zSlider.setBounds  (row.reduced (10));
}
