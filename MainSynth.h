#pragma once

#include "Parser/ast.h"
#include "Parser/eqast.h"
#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class MainSynth : public juce::AudioProcessor {
public:
  //==============================================================================
  MainSynth();
  ~MainSynth() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  void setExpression(AST *expr);
  void setYAuxes(std::vector<AST *> yAuxes);
  void setFrequency(double freq);
  AST *getExpr();
  std::vector<AST *> getYAuxes();
  juce::MidiKeyboardState keyboardState;

private:
  AST *expression;
  std::vector<AST *> yAuxes;

  // EqAST allASTs = EqAST("sin(f*2*3.14*x)", 8);
  std::shared_ptr<EqAST> allASTs = std::make_shared<EqAST>("sin(f*2*3.14*x)", 8);

  double currentSampleRate = 0.0, xCurrent = 0.0, xDelta = 0.0;
  double frequency = 440;
  juce::Random random;
  juce::Synthesiser synth;

  bool hasStarted = false;

  void initializeSynth();

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainSynth)
};
