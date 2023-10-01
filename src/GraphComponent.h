#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module
// headers directly. If you need to remain compatible with Projucer-generated
// builds, and have called `juce_generate_juce_header(<thisTarget>)` in your
// CMakeLists.txt, you could `#include <JuceHeader.h>` here instead, to make all
// your module headers visible.
#include "Parser/eqast.h"
#include <juce_gui_extra/juce_gui_extra.h>
// #include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class GraphComponent : public juce::Component {
public:
  //==============================================================================
  GraphComponent(std::shared_ptr<EqAST> alAST);

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  void setExpressionNum(int num);

private:
  //==============================================================================
  // Your private member variables go here...

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphComponent)

  float getXPixel(double xVal);
  float getYPixel(double yVal);

  int expressionNum = -1;

  std::shared_ptr<EqAST> allASTs;

  float xMin;
  float xMax;
  float yMin;
  float yMax;
};
