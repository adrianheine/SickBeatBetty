
#include "parambutton.h"

ParamButton::ParamButton(juce::RangedAudioParameter &param, juce::UndoManager *undoManager) :
    ToggleButton(),
    _attach(param, *this, undoManager),
    _param(param)
{
    _attach.sendInitialUpdate();
}

ParamButton::~ParamButton() {

}

void ParamButton::resetToDefault() {
    float val = _param.getDefaultValue();
    juce::Logger::writeToLog(juce::String("Resetting ") + _param.name + " to " + juce::String(val));
    _param.sendValueChangedMessageToListeners(val);
    _param.beginChangeGesture();
    _param.setValueNotifyingHost(val);
    _param.endChangeGesture();
    return;
}

