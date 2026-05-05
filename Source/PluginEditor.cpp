/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>

namespace
{
  constexpr int frameMargin = 12;
  constexpr float headerTopRatio = 0.06f;
  constexpr float headerHeightRatio = 0.19f;
  constexpr float controlTopRatio = 0.26f;
  constexpr float controlHeightRatio = 0.43f;
  constexpr float footerTopRatio = 0.83f;
  constexpr float footerHeightRatio = 0.10f;
}

//==============================================================================
DCOffsetterAudioProcessorEditor::DCOffsetterAudioProcessorEditor (DCOffsetterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
  setSize (320, 220);
  setOpaque (true);
  setLookAndFeel (&customLookAndFeel);

  auto configureSlider = [] (juce::Slider& slider)
  {
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    slider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xfff39c12));
    slider.setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff14181b));
    slider.setColour (juce::Slider::thumbColourId, juce::Colour (0xfff39c12));
    slider.setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xffffff00).withAlpha (0.6f));
    slider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xff3f454b));
  };

  configureSlider (dcOffsetSliderL);
  configureSlider (dcOffsetSliderR);

  addAndMakeVisible (dcOffsetSliderL);
  addAndMakeVisible (dcOffsetSliderR);

  dcOffsetLabelL.setText ("Left", juce::dontSendNotification);
  dcOffsetLabelL.setJustificationType (juce::Justification::centred);
  dcOffsetLabelL.setColour (juce::Label::textColourId, juce::Colour (0xffffff00).withAlpha (0.6f));
  addAndMakeVisible (dcOffsetLabelL);

  dcOffsetLabelR.setText ("Right", juce::dontSendNotification);
  dcOffsetLabelR.setJustificationType (juce::Justification::centred);
  dcOffsetLabelR.setColour (juce::Label::textColourId, juce::Colour (0xffffff00).withAlpha (0.6f));
  addAndMakeVisible (dcOffsetLabelR);

  dcOffsetAttachmentL = std::make_unique<SliderAttachment> (audioProcessor.apvts, Parameters::DCOFFSET_L_ID, dcOffsetSliderL);
  dcOffsetAttachmentR = std::make_unique<SliderAttachment> (audioProcessor.apvts, Parameters::DCOFFSET_R_ID, dcOffsetSliderR);
}

DCOffsetterAudioProcessorEditor::~DCOffsetterAudioProcessorEditor()
{
  setLookAndFeel (nullptr);
}

//==============================================================================
void DCOffsetterAudioProcessorEditor::paint (juce::Graphics& g)
{
  g.fillAll (juce::Colour (0xff111111));

  auto headerBounds = juce::Rectangle<int> (frameMargin,
                                              static_cast<int> (std::round (getHeight() * headerTopRatio)),
                        getWidth() - frameMargin * 2,
                                              static_cast<int> (std::round (getHeight() * headerHeightRatio)));
  g.setColour (juce::Colour (0xffffff00).withAlpha (0.6f));
  g.fillRoundedRectangle (headerBounds.toFloat(), 2.0f);

  auto headerLeftBounds = headerBounds.removeFromLeft (juce::jmax (1, (headerBounds.getWidth() * 2) / 3));
  auto headerRightBounds = headerBounds;

  auto footerBounds = juce::Rectangle<int> (frameMargin,
                                              static_cast<int> (std::round (getHeight() * footerTopRatio)),
                        getWidth() - frameMargin * 2,
                                              static_cast<int> (std::round (getHeight() * footerHeightRatio)));
  g.setColour (juce::Colour (0xffffff00).withAlpha (0.6f));
  g.fillRoundedRectangle (footerBounds.toFloat(), 2.0f);

  g.setColour (juce::Colours::black);
  g.setFont (juce::Font (22.0f, juce::Font::bold));
  g.drawFittedText ("DCOffsetter", headerLeftBounds, juce::Justification::centred, 1);
  g.setFont (juce::Font (12.0f));
  g.drawFittedText ("wheatBread\nPlugins", headerRightBounds, juce::Justification::centredLeft, 2);
  g.drawFittedText ("Make sure to remove the DC offset at the end.", footerBounds, juce::Justification::centred, 1);
}

void DCOffsetterAudioProcessorEditor::resized()
{
  auto controlTop = static_cast<int> (std::round (getHeight() * controlTopRatio));
  auto controlHeight = static_cast<int> (std::round (getHeight() * controlHeightRatio));
  auto knobWidth = static_cast<int> (std::round (getWidth() * 0.34f));
  auto knobY = controlTop + static_cast<int> (std::round ((getHeight() * controlHeightRatio - controlHeight) * 0.5f));
  auto labelHeight = static_cast<int> (std::round (getHeight() * 0.08f));
  auto labelY = controlTop + controlHeight + static_cast<int> (std::round (getHeight() * 0.02f));

  auto leftX = static_cast<int> (std::round (getWidth() * 0.08f));
  auto rightX = getWidth() - static_cast<int> (std::round (getWidth() * 0.08f)) - knobWidth;

  dcOffsetSliderL.setBounds (leftX, knobY, knobWidth, controlHeight);
  dcOffsetSliderR.setBounds (rightX, knobY, knobWidth, controlHeight);

  dcOffsetLabelL.setBounds (leftX, labelY, knobWidth, labelHeight);
  dcOffsetLabelR.setBounds (rightX, labelY, knobWidth, labelHeight);
}
