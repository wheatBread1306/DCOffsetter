#include "DCOffsetProcessor.h"

DCOffsetProcessor::DCOffsetProcessor() {
  dcOffset.setCurrentAndTargetValue(0.0f);
}

void DCOffsetProcessor::prepare(juce::dsp::ProcessSpec &spec) {
  dcOffset.reset(spec.sampleRate, 0.01); // Smooth over 10ms
  sampleRate = spec.sampleRate;
}

void DCOffsetProcessor::setDCOffset(float offset) {
  dcOffset.setTargetValue(offset);
}

void DCOffsetProcessor::process(float *samples, int numSamples) {
  using SIMDFloat = juce::dsp::SIMDRegister<float>;
  const int simdSize = (int)SIMDFloat::size();

  float currentOffset = dcOffset.getNextValue();
  SIMDFloat offsetReg(currentOffset);

  int i = 0;

  while (i < numSamples && !SIMDFloat::isSIMDAligned(samples + i)) {
    samples[i] += currentOffset;
    i++;
  }
  for (; i <= numSamples - simdSize; i += simdSize) {
    auto v = SIMDFloat::fromRawArray(samples + i);
    v = v + offsetReg;
    v.copyToRawArray(samples + i);
  }
  for (; i < numSamples; ++i) {
    samples[i] += currentOffset;
  }

  dcOffset.skip(numSamples - 1);
}

void DCOffsetProcessor::reset() { dcOffset.reset(sampleRate, 0.01); }