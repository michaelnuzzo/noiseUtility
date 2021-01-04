/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseUtilityAudioProcessor::NoiseUtilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
                    , parameters(*this, nullptr, "Parameters", createParameters())
{
    parameters.state = juce::ValueTree("Parameters");
}

NoiseUtilityAudioProcessor::~NoiseUtilityAudioProcessor()
{
}

//==============================================================================
const juce::String NoiseUtilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoiseUtilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoiseUtilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoiseUtilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoiseUtilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoiseUtilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoiseUtilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoiseUtilityAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NoiseUtilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoiseUtilityAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NoiseUtilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void NoiseUtilityAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoiseUtilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NoiseUtilityAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float g = juce::Decibels::decibelsToGain(float(*parameters.getRawParameterValue("GAIN")));

    for(int ch = 0; ch < totalNumInputChannels; ch++)
    {
        auto rp = buffer.getReadPointer(ch);
        auto wp = buffer.getWritePointer(ch);

        for(int i = 0; i < buffer.getNumSamples(); i++)
            wp[i] = rp[i] + ((random.nextFloat()*g) - g/2.);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout NoiseUtilityAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN"   , "Gain"   , juce::NormalisableRange<float>(-90.f, 0.f, 0.001f), -200.f));
    return { params.begin(), params.end() };
}

//==============================================================================
bool NoiseUtilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoiseUtilityAudioProcessor::createEditor()
{
    return new NoiseUtilityAudioProcessorEditor (*this);
}

//==============================================================================
void NoiseUtilityAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void NoiseUtilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if(xmlState.get() != nullptr)
    {
        if(xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.state = juce::ValueTree::fromXml(*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoiseUtilityAudioProcessor();
}
