#pragma once

#include "MainSynth.h"
#include "GraphComponent.h"

//==============================================================================
class MainEditor  : public juce::AudioProcessorEditor
{
public:
    explicit MainEditor (MainSynth&);
    ~MainEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MainSynth& processorRef;

    GraphComponent graph;

    juce::Label expressionInput;
    juce::Label yEqualsLabel;

    AST *expression;

    void setExpressionText(juce::String expr);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditor)
};
