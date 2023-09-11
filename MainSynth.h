#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "Parser/ast.h"

//==============================================================================
class MainSynth : public juce::AudioProcessor
{
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
    void setFrequency(double freq);

private:
    AST *expression;
    double currentSampleRate = 0.0, xCurrent = 0.0, xDelta = 0.0;
    double frequency = 440;
    juce::Random random;
    juce::Synthesiser synth;
    juce::MidiKeyboardState keyboardState;

    void initializeSynth();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainSynth)

};