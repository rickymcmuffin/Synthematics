#pragma once

#include "GraphComponent.h"
#include "MainSynth.h"
#include <juce_audio_utils/juce_audio_utils.h>
#include <vector>

#define NUM_YAUXES 8

//==============================================================================
class MainEditor : public juce::AudioProcessorEditor {
public:
  MainEditor(MainSynth &, std::shared_ptr<EqAST> alAST);
  ~MainEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  MainSynth &processorRef;

  GraphComponent graph;

  juce::Label expressionInput;
  juce::Label yEqualsLabel;
  juce::Label errorLabel;

  // The even indicies are error labels and odds are equations
  std::vector<std::unique_ptr<juce::Label>> errorsAndYAuxes;

  juce::Viewport equationsView;
  juce::MidiKeyboardComponent midiKeyboard;

  int lastEdited;

  std::shared_ptr<EqAST> allASTs;

  void init();
  void setExpressionText(juce::String expr);
  void changeYAuxText();

  void setGraphExpr();
  void resizeView();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainEditor)
};
