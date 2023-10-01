#include <juce_audio_processors/juce_audio_processors.h>
#include "Parser/eqast.h"

class WaveSound : public juce::SynthesiserSound
{
public:
	WaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
	bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

class WaveVoice : public juce::SynthesiserVoice
{
public:
	WaveVoice(std::shared_ptr<EqAST> allASTs);

	bool canPlaySound(juce::SynthesiserSound *sound) override;

	void startNote(int midiNoteNumber, float velocity,
				juce::SynthesiserSound * /*sound*/,
				int /*currentPitchWheelPosition*/) override;

	void stopNote(float /*velocity*/, bool allowTailOff) override;

	void pitchWheelMoved(int /*newValue*/) override;

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;

	void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

	using SynthesiserVoice::renderNextBlock;

private:
	double level = 0.0;
	double tailOff = 0.0;
	double xCurrent = 0.0, xDelta = 0.0;
	double frequency = 440;
  	std::shared_ptr<EqAST> allASTs;
};
