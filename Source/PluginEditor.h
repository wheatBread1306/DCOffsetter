/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel/CustomLooks.h"

//==============================================================================
/**
*/
class DCOffsetterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DCOffsetterAudioProcessorEditor (DCOffsetterAudioProcessor&);
    ~DCOffsetterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::Slider dcOffsetSliderL;
    juce::Slider dcOffsetSliderR;
    juce::Label dcOffsetLabelL;
    juce::Label dcOffsetLabelR;
    std::unique_ptr<SliderAttachment> dcOffsetAttachmentL;
    std::unique_ptr<SliderAttachment> dcOffsetAttachmentR;
    CustomLookAndFeel customLookAndFeel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DCOffsetterAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DCOffsetterAudioProcessorEditor)
};
