/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseUtilityAudioProcessorEditor::NoiseUtilityAudioProcessorEditor (NoiseUtilityAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //==========================================================================================//

    /* initialize */

    setSize (400, 400);

    // set global colour preferences
    getLookAndFeel().setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colours::white);
    getLookAndFeel().setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::white);
    getLookAndFeel().setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colours::white);

    //==========================================================================================//

    /* set parameters */

    // ymin slider
    gainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
    gainKnob.setTextValueSuffix(" dBFS");
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getParameters(),"GAIN",gainKnob);
    gainLabel.setText("Noise Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::horizontallyCentred);
    gainLabel.attachToComponent(&gainKnob, true);
    addAndMakeVisible(gainKnob);


    //==========================================================================================//

    gainKnob.setBounds(getWidth()/4, getHeight()/4, 200, 200 );
}

NoiseUtilityAudioProcessorEditor::~NoiseUtilityAudioProcessorEditor()
{
}

//==============================================================================
void NoiseUtilityAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);

}

void NoiseUtilityAudioProcessorEditor::resized()
{
}
