#include "GraphComponent.h"

using namespace std;
//==============================================================================
GraphComponent::GraphComponent()
{


    GraphComponent::expression = NULL;
    
    // setSize(600, 400);
    // GraphComponent::expression = p.parseExpression();

    // GraphComponent::expression = expression;

    xMin = 0;
    xMax = 1;
    yMin = -1;
    yMax = 1;
}

//==============================================================================
void GraphComponent::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::white);
    //  g.fillRect(30, 30, 0, 0);
    // g.setFont (juce::Font (16.0f));
    // g.setColour (juce::Colours::black);
    // g.drawText ("Hello \nWorld!", getLocalBounds(), juce::Justification::centred, true);

    g.setColour(juce::Colours::grey);

    g.drawLine(getXPixel(0)*1.0f, 0, getXPixel(0)*1.0f, getHeight()*1.0f);
    g.drawLine(0, getYPixel(0), getWidth()*1.0f, getYPixel(0));

    // double xPrecision = (xMax - xMin) / 10;

    try
    {
        g.setColour(juce::Colours::blueviolet);
        double firstYVal = resultExpression(expression, xMin);
        // g.drawText(unparseExpression(expression), getLocalBounds(), juce::Justification::bottom, true);
        double interval = (xMax - xMin)/getWidth();

        for (double x = xMin; x < xMax; x += interval)
        {

            double newYVal = resultExpression(expression, x + interval, 1, yAuxes);
            // cout << "x: " << x + interval <<", y: " << newYVal<<endl;

            g.drawLine(getXPixel(x), getYPixel(firstYVal), getXPixel(x + interval), getYPixel(newYVal), 2);

            firstYVal = newYVal;
        }

        g.setColour(juce::Colours::black);
        g.drawText(unparseExpression(expression), getLocalBounds(), juce::Justification::topLeft, true);

        stringstream stream;

        stream << "Min x: " << setprecision(3) << xMin << ", Max x: " << setprecision(3) << xMax << '\n';
        stream << "Min y: " << setprecision(3) << yMin << ", Max y: " << setprecision(3) << yMax;

        string minMax = stream.str();

        g.drawFittedText(minMax, getLocalBounds(), juce::Justification::topRight, 2);
    }
    catch (EquationException e)
    {
        g.drawText(e.what(), getLocalBounds(), juce::Justification::top, true);
    }
    catch (std::exception e){
        g.drawText(e.what(), getLocalBounds(), juce::Justification::top, true);
    }
}

float GraphComponent::getXPixel(double xVal)
{
    float ret = (float)((xVal*1.0f - xMin) / (xMax - xMin));

    return getWidth() * ret;
}

float GraphComponent::getYPixel(double yVal)
{
    float ret = (float)((yVal - yMin) / (yMax - yMin));

    return getHeight() * (1 - ret);
}

void GraphComponent::resized()
{
    // This is called when the GraphComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

}

void GraphComponent::setExpression(AST *ast){
    GraphComponent::expression = ast;
    repaint();
}
    
void GraphComponent::setYAuxes(std::vector<AST *> yA){
    GraphComponent::yAuxes = yA;
    repaint();
}
