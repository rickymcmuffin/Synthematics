#include "MainEditor.h"
#include "MainSynth.h"
#include <sstream>

MainEditor::MainEditor(MainSynth &p, std::shared_ptr<EqAST> alAST)
    : AudioProcessorEditor(&p), processorRef(p), graph(alAST),
      midiKeyboard(p.keyboardState,
                   juce::MidiKeyboardComponent::horizontalKeyboard) {
  allASTs = alAST;
  init();
}
MainEditor::~MainEditor() {}

void MainEditor::init() {

  addAndMakeVisible(graph);

  addAndMakeVisible(equationsView);

  equationsView.addAndMakeVisible(errorLabel);
  errorLabel.setColour(juce::Label::textColourId, juce::Colours::red);

  equationsView.addAndMakeVisible(expressionInput);
  expressionInput.setEditable(true);
  expressionInput.setColour(juce::Label::backgroundColourId,
                            juce::Colours::darkblue);
  expressionInput.setColour(juce::Label::textColourId, juce::Colours::white);
  expressionInput.onTextChange = [this] {
    setExpressionText(expressionInput.getText());
    setGraphExpr();
  };
  expressionInput.onEditorShow = [this] { setGraphExpr(); };
  expressionInput.setText(allASTs->toString(), juce::dontSendNotification);

  equationsView.addAndMakeVisible(yEqualsLabel);
  yEqualsLabel.attachToComponent(&expressionInput, true);
  yEqualsLabel.setText("y = ", juce::dontSendNotification);

  for (size_t i = 0; i < NUM_YAUXES; i++) {
    juce::Label *inputBox = new juce::Label();
    juce::Label *errorText = new juce::Label();
    juce::Label *yAuxEquals = new juce::Label();

    equationsView.addAndMakeVisible(errorText);
    errorText->setColour(juce::Label::textColourId, juce::Colours::red);
    errorsAndYAuxes.emplace_back(errorText);

    equationsView.addAndMakeVisible(inputBox);
    inputBox->setEditable(true);
    inputBox->setColour(juce::Label::backgroundColourId,
                        juce::Colours::darkblue);
    inputBox->setColour(juce::Label::textColourId, juce::Colours::white);
    inputBox->onTextChange = [this] {
      changeYAuxText();
      setGraphExpr();
    };
    inputBox->onEditorShow = [this] { setGraphExpr(); };
    inputBox->setText(allASTs->toString(i), juce::dontSendNotification);

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

  setExpressionText(allASTs->toString());
  changeYAuxText();

  setSize(1000, 480);
  lastEdited = -1;
  // std::cout << "whY"<<std::endl;
}

//==============================================================================
void MainEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  // g.drawFittedText ("Hello World!", getLocalBounds(),
  // juce::Justification::centred, 1);
}

void MainEditor::resized() {
  auto r = getLocalBounds().reduced(8);
  equationsView.setBounds(0, 0, 400, 400);
  midiKeyboard.setBounds(r.removeFromBottom(70));
  graph.setBounds(400, 0, getWidth() - 400, 400);

  // equationsView bounds
  resizeView();
}

void MainEditor::setExpressionText(juce::String expr) {

  errorLabel.setText("", juce::dontSendNotification);
  std::string s = expr.toStdString();

  try {
    allASTs->setExpression(s);
  } catch (EquationException e) {
    errorLabel.setText(e.what(), juce::dontSendNotification);
  }
}
void MainEditor::changeYAuxText() {
  for (size_t i = 1; i < errorsAndYAuxes.size(); i += 2) {
    errorsAndYAuxes[i - 1]->setText("", juce::dontSendNotification);
    std::string s = errorsAndYAuxes[i]->getText().toStdString();
    try {
      allASTs->setExpression(s, i / 2);

    } catch (EquationException e) {
      errorsAndYAuxes[i - 1]->setText(e.what(), juce::dontSendNotification);
    }
  }
}
void MainEditor::resizeView() {
  errorLabel.setBounds(50, 0, equationsView.getWidth() - 80, 20);
  expressionInput.setBounds(50, 20, equationsView.getWidth() - 80, 20);

  for (size_t i = 0; i < errorsAndYAuxes.size(); i++) {

    errorsAndYAuxes[i]->setBounds(50, ((int)i + 2) * 20,
                                  equationsView.getWidth() - 80, 20);
  }
}

void MainEditor::setGraphExpr() {
  if (expressionInput.isBeingEdited()) {
    graph.setExpressionNum(-1);
    lastEdited = -1;
    return;
  }
  for (size_t i = 0; i < NUM_YAUXES; i++) {
    if (errorsAndYAuxes[2 * i + 1]->isBeingEdited()) {
      graph.setExpressionNum((int)i);
      lastEdited = (int)i;
      return;
    }
  }
  graph.setExpressionNum(lastEdited);
}
