#include "CustomLooks.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xfff1c40f));
    setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff111418));
    setColour (juce::Slider::thumbColourId, juce::Colour (0xfff1c40f));
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float> (static_cast<float> (x), static_cast<float> (y),
                                          static_cast<float> (width), static_cast<float> (height)).reduced (4.0f);
    auto size = juce::jmin (bounds.getWidth(), bounds.getHeight());
    auto center = bounds.getCentre();
    auto radius = size * 0.5f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Draw black circle
    g.setColour (juce::Colour (0xffffff00).withAlpha (0.6f));
    g.fillEllipse (juce::Rectangle<float> (center.x - radius, center.y - radius, size, size));

    // Draw yellow needle from circumference inward
    auto needleStart = center.getPointOnCircumference (radius, angle);
    auto needleEnd = center.getPointOnCircumference (radius * 0.35f, angle);
    g.setColour (juce::Colour (0xff000000));
    g.drawLine (juce::Line<float> (needleStart, needleEnd), radius * 0.08f);

    juce::ignoreUnused (slider);
}