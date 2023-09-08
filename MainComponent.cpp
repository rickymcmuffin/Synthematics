#include "MainComponent.h"

MainComponent::MainComponent()
{
	Parser p = Parser("sin(220 * 2 * 3.14 * x) + sin(729/512 * 220 * 2 * 3.14 * x)");
	expression = p.parseExpression();
	// MainComponent::graph = GraphComponent(expression);

	addAndMakeVisible(graph);
	graph.setExpression(expression);
	setSize(600, 600);
	setAudioChannels(0, 2);
	cout << unparseExpression(expression);
}

MainComponent::~MainComponent()
{
	shutdownAudio();
}

void MainComponent::paint(juce::Graphics &g)
{
}

void MainComponent::resized()
{
	graph.setBounds(0, 0, getWidth(), getHeight() - 200);
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	juce::String message;
	message << "Preparing to play audio...\n";
	message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
	message << " sampleRate = " << sampleRate;
	juce::Logger::getCurrentLogger()->writeToLog(message);
	currentSampleRate = sampleRate;
	xDelta = 1 / currentSampleRate;
	updateAngleDelta();
}
void MainComponent::updateAngleDelta()
{
	auto cyclesPerSample = 440 / currentSampleRate;					// [2]
	angleDelta = cyclesPerSample * 2.0 * 3.14; // [3]
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
	float level = 1.0f;
	// cout << "started getNextAudioBlock" << endl;
	// cout << "started getFirstFor" << endl;
	// Get a pointer to the start sample in the buffer for this audio output channel
	auto *leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
	auto *rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
	// cout << bufferToFill.numSamples<<endl;
	// Fill the required number of samples with noise between -0.125 and +0.125
	for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
	{
		// cout << "started SecondFor" << endl;
		// Get a pointer to the start sample in the buffer for this audio output channel
		// double x = 2 * 3.14159 * 440 * (xCurrent + sample * xDelta);
		// currentAngle += angleDelta;
		// leftBuffer[sample] = sin(currentAngle) *level;
		// rightBuffer[sample] = sin(currentAngle) *level;

		xCurrent += xDelta;
		double res = resultExpression(expression, xCurrent) * level;
		leftBuffer[sample] = res;
		rightBuffer[sample] = res;
	}
	// xCurrent += bufferToFill.numSamples * xDelta;
}
void MainComponent::releaseResources()
{
	juce::Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
}