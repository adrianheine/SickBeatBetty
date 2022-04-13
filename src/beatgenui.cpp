#include "beatgenui.h"

#define TEXTBOX_WIDTH       50
#define TEXTBOX_HEIGHT      20

BeatGenUI::BeatGenUI(BeatGen &beatGen) :
    juce::Component(),
    _enabled(*beatGen.getParameter(BeatGen::ParamEnabled)->param()),
    _note(*beatGen.getParameter(BeatGen::ParamNote)->param()),
    _steps(*beatGen.getParameter(BeatGen::ParamSteps)->param()),
    _phaseOffset(*beatGen.getParameter(BeatGen::ParamPhaseOffset)->param()),
    _bars(*beatGen.getParameter(BeatGen::ParamBars)->param()),
    _level(*beatGen.getParameter(BeatGen::ParamLevel)->param()),
    _beatGen(beatGen)
{    
    _enabled.setButtonText("Enabled");
    _enabled.setToggleable(true);
    _enabled.setTooltip("Enables this beat generator");
    addAndMakeVisible(_enabled);

    _labelNote.setText("Note", juce::dontSendNotification);
    addAndMakeVisible(_labelNote);

    _note.setSliderStyle(juce::Slider::LinearHorizontal);
    _note.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    _note.setTooltip("Note this beat generator will output");
    addAndMakeVisible(_note);

    _labelSteps.setText("Steps", juce::dontSendNotification);
    addAndMakeVisible(_labelSteps);

    _steps.setSliderStyle(juce::Slider::LinearHorizontal);
    _steps.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    _steps.setTooltip("Total number of steps this beat generator should output");
    addAndMakeVisible(_steps);

    _labelPhaseOffset.setText("Phase", juce::dontSendNotification);
    addAndMakeVisible(_labelPhaseOffset);

    _phaseOffset.setSliderStyle(juce::Slider::LinearHorizontal);
    _phaseOffset.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    _phaseOffset.setTooltip("The phase offset relative to the start of the generation");
    addAndMakeVisible(_phaseOffset);

    _labelBars.setText("Bars", juce::dontSendNotification);
    addAndMakeVisible(_labelBars);

    _bars.setSliderStyle(juce::Slider::LinearHorizontal);
    _bars.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    _bars.setTooltip("Total number of bars these steps should cover");
    addAndMakeVisible(_bars);

    _labelLevel.setText("Level", juce::dontSendNotification);
    addAndMakeVisible(_labelLevel);

    _level.setSliderStyle(juce::Slider::LinearHorizontal);
    _level.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
    _level.setTooltip("Starting level of this generator's note.  Can be modified by each clock");
    addAndMakeVisible(_level);

    for(int i = 0; i < BeatGen::maxClockCount; i++) {
        _clocks.add(std::make_unique<BeatGenClockUI>(_beatGen, i));
        addAndMakeVisible(_clocks[i]);
    }
}

BeatGenUI::~BeatGenUI() {

}

void BeatGenUI::paint(juce::Graphics &g) {
    juce::ignoreUnused(g);
    return;
}

void BeatGenUI::resized() {
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using Px = juce::Grid::Px;
    using Item = juce::GridItem;

    auto r = getLocalBounds();
    _enabled.setBounds(r.removeFromTop(TEXTBOX_HEIGHT));

    grid.templateRows = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };
    grid.templateColumns = { Track(Px(50)), Track(Fr(1)) };
    grid.items = {
        Item(_labelNote), Item(_note),
        Item(_labelLevel), Item(_level),
        Item(_labelSteps), Item(_steps),
        Item(_labelBars), Item(_bars),
        Item(_labelPhaseOffset), Item(_phaseOffset)
    };
    grid.performLayout(r.removeFromTop(TEXTBOX_HEIGHT * 5));    

    grid = juce::Grid();
    grid.templateRows = { Track(Fr(1)) };
    for(int i = 0; i < _clocks.size(); i++) {
        grid.templateColumns.add(Track(Fr(1)));
        grid.items.add(Item(*_clocks[i]));
    };
    grid.performLayout(r);
    return;
}
