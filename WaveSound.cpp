#include "WaveSound.h"
#include "Parser/unparseMath.h"

WaveVoice::WaveVoice(AST *expr, std::vector<AST *> yA)
{
	WaveVoice::expression = expr;
	WaveVoice::yAuxes = yA;
}

bool WaveVoice::canPlaySound(juce::SynthesiserSound *sound)
{
	return dynamic_cast<WaveSound *>(sound) != nullptr;
}

void WaveVoice::startNote(int midiNoteNumber, float velocity,
					 juce::SynthesiserSound * /*sound*/,
					 int /*currentPitchWheelPosition*/)
{
	xCurrent = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

	xDelta = 1 / getSampleRate();
}

void WaveVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
	if (allowTailOff)
	{
		// start a tail-off by setting this flag. The render callback will pick up on
		// this and do a fade out, calling clearCurrentNote() when it's finished.

		if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
						// stopNote method could be called more than once.
			tailOff = 1.0;
		// clearCurrentNote();
		// xDelta = 0.0;
	}
	else
	{
		// we're being told to stop playing immediately, so reset everything..

		clearCurrentNote();
		xDelta = 0.0;
	}
}

void WaveVoice::pitchWheelMoved(int /*newValue*/)
{
}

void WaveVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/)
{
}

void WaveVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	if (xDelta != 0.0)
	{
		while (--numSamples >= 0)
		{
			auto currentSample = (float)resultExpression(expression, xCurrent, frequency, yAuxes);

			if (currentSample > 1)
			{
				currentSample = 1;
			}
			else if (currentSample < -1)
			{
				currentSample = -1;
			}
			currentSample *= (float)level;
			if (tailOff > 0)
			{
				currentSample *= (float)tailOff;
				tailOff *= 0.99;
				if(tailOff <= 0.005){
					clearCurrentNote();
					xDelta = 0.0;
					break;
				}
			}

			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample(i, startSample, currentSample);

			xCurrent += xDelta;
			++startSample;
		}
	}
}