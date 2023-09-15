#include "MainSynth.h"
#include "MainEditor.h"
#include <sstream>

#define NUM_YAUXES 6
//==============================================================================
MainEditor::MainEditor(MainSynth &p)
    : AudioProcessorEditor(&p), processorRef(p),
      midiKeyboard(p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{

    // MainEditor::processorRef = p;
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    // MainComponent::graph = GraphComponent(expression);
    juce::String expr = "sin(f * 2 * 3.14 * x)";

    addAndMakeVisible(graph);

    addAndMakeVisible(equationsView);

    equationsView.addAndMakeVisible(errorLabel);
    errorLabel.setColour(juce::Label::textColourId, juce::Colours::red);

    equationsView.addAndMakeVisible(expressionInput);
    expressionInput.setEditable(true);
    expressionInput.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    expressionInput.onTextChange = [this]
    {
        setExpressionText(expressionInput.getText());
    };
    expressionInput.onEditorShow = [this]
    {
        std::cout <<"hello"<<std::endl;
    };
    expressionInput.setText(expr, juce::dontSendNotification);

    equationsView.addAndMakeVisible(yEqualsLabel);
    yEqualsLabel.attachToComponent(&expressionInput, true);
    yEqualsLabel.setText("y = ", juce::dontSendNotification);

    yAuxes.resize(NUM_YAUXES);

    for (int i = 0; i < NUM_YAUXES; i++)
    {
        juce::Label *inputBox = new juce::Label();
        juce::Label *errorText = new juce::Label();
        juce::Label *yAuxEquals = new juce::Label();

        equationsView.addAndMakeVisible(errorText);
        errorText->setColour(juce::Label::textColourId, juce::Colours::red);
        errorsAndYAuxes.emplace_back(errorText);

        equationsView.addAndMakeVisible(inputBox);
        inputBox->setEditable(true);
        inputBox->setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
        inputBox->onTextChange = [this]
        {
            changeYAuxText();
        };
        inputBox->onEditorShow = [this]
        {
            setGraphExpr(inputBox);
        };

        equationsView.addAndMakeVisible(yAuxEquals);
        yAuxEquals->attachToComponent(inputBox, true);
        std::stringstream ss;
        ss << "y" << i << " = ";
        yAuxEquals->setText(ss.str(), juce::dontSendNotification);

        errorsAndYAuxes.emplace_back(inputBox);

        // std::cout << errorsAndYAuxes[i+1]->getText()<<std::endl;
    }

    addAndMakeVisible(midiKeyboard);

    expressionInput.setJustificationType(juce::Justification::bottom);

    setExpressionText(expr);

    setSize(1000, 480);
}

MainEditor::~MainEditor()
{
}

//==============================================================================
void MainEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MainEditor::resized()
{
    auto r = getLocalBounds().reduced(8);
    equationsView.setBounds(0, 0, 400, 400);
    midiKeyboard.setBounds(r.removeFromBottom(70));
    graph.setBounds(400, 0, getWidth()-400, 400);

    // equationsView bounds
    resizeView();
}

void MainEditor::setExpressionText(juce::String expr)
{

    errorLabel.setText("", juce::dontSendNotification);
    std::string s = expr.toStdString();
    Parser p = Parser(s);

    try
    {
        MainEditor::expression = p.parseExpression();

        MainEditor::graph.setExpression(MainEditor::expression);
        MainEditor::processorRef.setExpression(MainEditor::expression);
    }
    catch (EquationException e)
    {
        errorLabel.setText(e.what(), juce::dontSendNotification);
    }
}
void MainEditor::changeYAuxText()
{
    for (int i = 1; i < errorsAndYAuxes.size(); i += 2)
    {
        errorsAndYAuxes[i - 1]->setText("", juce::dontSendNotification);
        std::string s = errorsAndYAuxes[i]->getText().toStdString();
        Parser p = Parser(s);
        if (errorsAndYAuxes[i]->getText().compare("") != 0)
        {
            try
            {
                yAuxes[i / 2] = p.parseExpression();
            }
            catch (EquationException e)
            {
                errorsAndYAuxes[i - 1]->setText(e.what(), juce::dontSendNotification);
            }
        }
    }
    processorRef.setYAuxes(yAuxes);
    graph.setYAuxes(yAuxes);
}
void MainEditor::resizeView()
{
    errorLabel.setBounds(50, 0, equationsView.getWidth() - 80, 20);
    expressionInput.setBounds(50, 20, equationsView.getWidth() - 80, 20);

    for (int i = 0; i < errorsAndYAuxes.size(); i++)
    {

        errorsAndYAuxes[i]->setBounds(50, (i + 2) * 20, equationsView.getWidth() - 80, 20);
    }
}

void MainEditor::setGraphExpr(AST *ast){
    std::string s = input.getText().toStdStr();
    
    Parser p = Parser(s);

}