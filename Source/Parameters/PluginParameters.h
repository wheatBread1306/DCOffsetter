/*
  ==============================================================================

    PluginParameters.h
    パラメータID定義ファイル

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Parameters
{
    constexpr auto DCOFFSET_L_ID = "Param_6fefc2df";
    constexpr auto DCOFFSET_L_NAME = "L Bias";

    constexpr auto DCOFFSET_R_ID = "Param_1755f0e7";
    constexpr auto DCOFFSET_R_NAME = "R Bias";

    // パラメータのセットアップ関数
    inline juce::AudioProcessorValueTreeState::ParameterLayout
    createParameterLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout layout;

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            DCOFFSET_L_ID, DCOFFSET_L_NAME,
            juce::NormalisableRange<float>(-1.0f, 1.0f), 0.0f,
            juce::String(), juce::AudioProcessorParameter::genericParameter,
            [](float value, int)
            { return juce::String(value, 2); },
            [](const juce::String &text)
            { return text.getFloatValue(); }));

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            DCOFFSET_R_ID, DCOFFSET_R_NAME,
            juce::NormalisableRange<float>(-1.0f, 1.0f), 0.0f,
            juce::String(), juce::AudioProcessorParameter::genericParameter,
            [](float value, int)
            { return juce::String(value, 2); },
            [](const juce::String &text)
            { return text.getFloatValue(); }));

        return layout;
    }
}
