#pragma once

#include "MainSynth.h"
#include "GraphComponent.h"
#include <juce_audio_utils/juce_audio_utils.h>
#include <Vector>

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
    juce::Label errorLabel;

    // The even indicies are error labels and odds are equations
    std::vector<std::unique_ptr<juce::Label>> errorsAndYAuxes;

    std::vector<AST *> yAuxes;

    juce::Viewport equationsView;
    juce::MidiKeyboardComponent midiKeyboard;

    AST *expression;

    void setExpressionText(juce::String expr);
    void changeYAuxText();

    void setGraphExpr(juce:: Label input);
    void resizeView();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainEditor)
};
