#pragma once

#include <JuceHeader.h>

class DCOffsetProcessor
{
public:
    DCOffsetProcessor();
    ~DCOffsetProcessor() = default;

    void prepare(juce::dsp::ProcessSpec &spec);
    void setDCOffset(float offset);
    void process(float* samples, int numSamples);
    void reset();

private:
    juce::SmoothedValue<float> dcOffset{0.0f};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DCOffsetProcessor)
};