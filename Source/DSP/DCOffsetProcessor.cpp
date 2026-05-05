#include "DCOffsetProcessor.h"

void DCOffsetProcessor::prepare(juce::dsp::ProcessSpec &spec)
{
    dcOffset.reset(spec.sampleRate, 0.01); // Smooth over 10ms
}

void DCOffsetProcessor::setDCOffset(float offset)
{
    dcOffset.setTargetValue(offset);
}

void DCOffsetProcessor::process(float* samples, int numSamples)
{
    using SIMDFloat = juce::dsp::SIMDRegister<float>;
    const int simdSize = (int) SIMDFloat::size();
    int i = 0;
    for (; i <= numSamples - simdSize; i += simdSize)
    {
        auto v = SIMDFloat::fromRawArray (samples + i);
        SIMDFloat offset;
        for (int s = 0; s < simdSize; ++s)
            offset.set (s, dcOffset.getNextValue());
        v = v + offset;
        v.copyToRawArray (samples + i);
    }
    for (; i < numSamples; ++i)
    {
        samples[i] += dcOffset.getNextValue();
    }
}

void DCOffsetProcessor::reset()
{
    dcOffset.setCurrentAndTargetValue(0.0f);
}