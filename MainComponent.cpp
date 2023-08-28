#include "MainComponent.h"

#define WIDTH 600
#define HEIGHT 400

//==============================================================================
MainComponent::MainComponent()
{
    setSize(600, 400);
    Parser p = Parser("1-x*x");
    MainComponent::expression = p.parseExpression();
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (juce::Colours::white);
    //  g.fillRect(30, 30, 0, 0);
    // g.setFont (juce::Font (16.0f));
    // g.setColour (juce::Colours::black);
    // g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);

    try
    {
        float lastYVal = resultExpression(expression, 0);
        g.drawText(unparseExpression(expression), getLocalBounds(), juce::Justification::bottom, true);
        for (float x = 0.01; x <= 1.00; x += 0.01)
        {
            float yVal = resultExpression(expression, x);
            g.drawLine(WIDTH * (x - 0.01), HEIGHT * (1 - lastYVal), WIDTH * (x), HEIGHT * (1 - yVal), 1);

            lastYVal = yVal;
        }
    }
    catch (EquationException e)
    {
        g.drawText(e.what(), getLocalBounds(), juce::Justification::top, true);


    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
