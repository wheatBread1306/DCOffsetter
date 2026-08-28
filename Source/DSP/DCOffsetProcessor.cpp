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

  size_t i = 0;
  while (i + 8 <= static_cast<size_t>(numSamples)) {
    std::array<float, 8> dc{};
    for (size_t j = 0; j < 8; ++j) {
      dc[j] = dcOffset.getNextValue();
    }

    for (size_t j = 0; j < 8; ++j) {
      samples[i + j] += dc[j];
    }

    i += 8;
  }
  for (; i < static_cast<size_t>(numSamples); ++i) {
    samples[i] += dcOffset.getNextValue();
  }
}

void DCOffsetProcessor::reset() { dcOffset.reset(sampleRate, 0.01); }