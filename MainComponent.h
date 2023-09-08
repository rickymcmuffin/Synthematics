#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "GraphComponent.h"

class MainComponent : public juce::AudioAppComponent
{
public:
	MainComponent();
	~MainComponent();

	void paint(juce::Graphics &) override;
	void resized() override;
	void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    	void releaseResources() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
	GraphComponent graph;

	juce::Random random;

	AST *expression;
	double currentSampleRate = 0.0, xCurrent = 0.0, xDelta = 0.0;
	double angleDelta = 0.0, currentAngle = 0.0;
	void updateAngleDelta();
};