#include "MainComponent.h"

MainComponent::MainComponent(){
	addAndMakeVisible(graph);
	setSize(600, 600);

}

void MainComponent::paint(juce::Graphics &g){

}

void MainComponent::resized(){
	graph.setBounds(0, 0, getWidth(), getHeight() - 200);
}