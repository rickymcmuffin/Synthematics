#include "MainSynth.h"
#include "MainEditor.h"

//==============================================================================
MainEditor::MainEditor (MainSynth& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	Parser parse = Parser("sin(440 * 2 * 3.14 * x)");
	expression = parse.parseExpression();
	// MainComponent::graph = GraphComponent(expression);

	addAndMakeVisible(graph);
	graph.setExpression(expression);
    p.setExpression(expression);
	setSize(600, 600);
}

MainEditor::~MainEditor()
{
}

//==============================================================================
void MainEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MainEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
