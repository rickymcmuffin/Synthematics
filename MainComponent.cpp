#include "MainComponent.h"

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
        float firstYVal = resultExpression(expression, 0);
        g.drawText(unparseExpression(expression), getLocalBounds(), juce::Justification::bottom, true);
        float interval = 0.01f;

        for (float x = 0; x < 1; x += interval)
        {
            float newYVal = resultExpression(expression, x + interval);
            g.drawLine(getWidth() * x, getHeight() * (1 - firstYVal), getWidth() * (x + interval), getHeight() * (1 - newYVal), 1);

            firstYVal = newYVal;
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
