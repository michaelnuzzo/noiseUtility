/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NoiseUtilityAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NoiseUtilityAudioProcessorEditor (NoiseUtilityAudioProcessor&);
    ~NoiseUtilityAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    NoiseUtilityAudioProcessor& audioProcessor;
    juce::Label gainLabel;
    juce::Slider gainKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseUtilityAudioProcessorEditor);
};
