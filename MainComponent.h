#include <juce_gui_extra/juce_gui_extra.h>
#include "GraphComponent.h"

class MainComponent : public juce::Component
{
public:
	MainComponent();

	void paint(juce::Graphics &) override;
	void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
	GraphComponent graph;
};