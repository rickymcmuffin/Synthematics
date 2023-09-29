#include "MainSynth.h"
#include "MainEditor.h"
#include "WaveSound.h"
#include "Parser/unparseMath.h"

#define PLUGIN_NAME "Synthematics"

//==============================================================================
MainSynth::MainSynth()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )
{
    DBG("starting...");

    // to be deleted one day
    MainSynth::expression = Parser("sin(f*2*3.14*x)").parseExpression();
    yAuxes = std::vector<AST *>(NUM_YAUXES);
    std::fill(yAuxes.begin(), yAuxes.end(), nullptr);

    std::vector<std::string> yAuxesStrs = std::vector<std::string>(NUM_YAUXES);
    std::fill(yAuxesStrs.begin(), yAuxesStrs.end(), "");
    allASTs.setExpression("sin(f*2*3.14*x)", -1);
    for(int i = 0; i < NUM_YAUXES; i++){
        allASTs.setExpression("", i);
    }
    hasStarted = true;
}

MainSynth::~MainSynth()
{
}

//==============================================================================
const juce::String MainSynth::getName() const
{
    return PLUGIN_NAME;
}

bool MainSynth::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MainSynth::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool MainSynth::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double MainSynth::getTailLengthSeconds() const
{
    return 0.0;
}

int MainSynth::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int MainSynth::getCurrentProgram()
{
    return 0;
}

void MainSynth::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String MainSynth::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return "Synthematics";
}

void MainSynth::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void MainSynth::prepareToPlay(double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    MainSynth::xDelta = 1 / sampleRate;
    initializeSynth();
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void MainSynth::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool MainSynth::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void MainSynth::processBlock(juce::AudioBuffer<float> &buffer,
                             juce::MidiBuffer &midiMessages)
{
    DBG("starting...2");

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    int numSamples = buffer.getNumSamples();

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);

    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool MainSynth::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *MainSynth::createEditor()
{
    // if (!hasStarted)
    // {
    //     hasStarted = true;
    //     return new MainEditor(*this);
    // }
    // std::cout << "bor" <<std::endl;
    // std::string yStr = unparseExpression(expression); 
    // std::vector<std::string> yAuxStrs(yAuxes.size());
    // for(int i = 0; i < yAuxes.size(); i++){
    //     yAuxStrs[i] = unparseExpression(yAuxes[i]);
    // }
    // return new MainEditor(*this, yStr, yAuxStrs);
    return new MainEditor(*this);
}

//==============================================================================
void MainSynth::getStateInformation(juce::MemoryBlock &destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::XmlElement xml("ExpressionData");

    std::string yStr = unparseExpression(expression);
    xml.setAttribute("y", yStr);
    
    for(int i = 0; i < yAuxes.size(); i++){
        yStr = unparseExpression(yAuxes[i]);
        juce::String jStr("y" + std::to_string(i));
        xml.setAttribute(jStr, yStr);
    }

    copyXmlToBinary(xml, destData);
}

void MainSynth::setStateInformation(const void *data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if(xmlState.get() != nullptr){

        juce::String yStr = xmlState->getStringAttribute("y");
        // std::cout << yStr.toStdString() << std::endl;
        expression = Parser(yStr.toStdString()).parseExpression();

        yAuxes = std::vector<AST *>(NUM_YAUXES);
        for(int i = 0; i < NUM_YAUXES; i++){
            juce::String yAuxStr = xmlState->getStringAttribute("y" + std::to_string(i));
            // std::cout << yAuxStr.toStdString() << std::endl;
            yAuxes[i] = Parser(yAuxStr.toStdString()).parseExpression();
        }        

        hasStarted = true;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new MainSynth();
}

void MainSynth::setExpression(AST *expr)
{
    MainSynth::expression = expr;
    xCurrent = 0;
    initializeSynth();
}

void MainSynth::setYAuxes(std::vector<AST *> yA)
{
    MainSynth::yAuxes = yA;
    initializeSynth();
}

void MainSynth::setFrequency(double freq)
{
    MainSynth::frequency = freq;
    xCurrent = 0;
}

void MainSynth::initializeSynth()
{
    synth.clearSounds();
    synth.clearVoices();
    auto numVoices = 8;

    // Add some voices...
    for (auto i = 0; i < numVoices; ++i)
        synth.addVoice(new WaveVoice(expression, yAuxes));

    // ..and give the synth a sound to play
    synth.addSound(new WaveSound());
}

    
AST *MainSynth::getExpr(){
    return MainSynth::expression;
}
std::vector<AST *> MainSynth::getYAuxes(){
    return MainSynth::yAuxes;
}
