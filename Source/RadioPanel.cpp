/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include <stdio.h>
#include "AudioPath.h"
//[/Headers]

#include "RadioPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#ifdef WIN32
#define snprintf _snprintf
#endif
//[/MiscUserDefs]

//==============================================================================
RadioPanel::RadioPanel ()
{
    addAndMakeVisible (Spectrum = new SpectrumScope());
    Spectrum->setName ("SpectrumScope");

    addAndMakeVisible (label_freq = new Label ("frequency",
                                               "LO Frequency"));
    label_freq->setFont (Font (15.00f, Font::bold));
    label_freq->setJustificationType (Justification::centredLeft);
    label_freq->setEditable (false, false, false);
    label_freq->setColour (TextEditor::textColourId, Colours::black);
    label_freq->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label_lo_freq = new Label ("new label",
                                                  "00.000000"));
    label_lo_freq->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
    label_lo_freq->setJustificationType (Justification::centred);
    label_lo_freq->setEditable (false, false, false);
    label_lo_freq->setColour (Label::backgroundColourId, Colour (0xff44d01c));
    label_lo_freq->setColour (TextEditor::textColourId, Colours::black);
    label_lo_freq->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label_tune = new Label ("new label",
                                               "Tune frequency"));
    label_tune->setFont (Font (15.00f, Font::bold));
    label_tune->setJustificationType (Justification::centredLeft);
    label_tune->setEditable (false, false, false);
    label_tune->setColour (TextEditor::textColourId, Colours::black);
    label_tune->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label_tune_freq = new Label ("new label",
                                                    "00.000000"));
    label_tune_freq->setFont (Font (Font::getDefaultMonospacedFontName(), 18.00f, Font::bold));
    label_tune_freq->setJustificationType (Justification::centred);
    label_tune_freq->setEditable (false, false, false);
    label_tune_freq->setColour (Label::backgroundColourId, Colour (0xff44d01c));
    label_tune_freq->setColour (TextEditor::textColourId, Colours::black);
    label_tune_freq->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (next_band = new TextButton ("new button"));
    next_band->setButtonText ("Band Up");
    next_band->addListener (this);

    addAndMakeVisible (prev_band = new TextButton ("new button"));
    prev_band->setButtonText ("Band Down");
    prev_band->addListener (this);

    addAndMakeVisible (toggleLSB = new ToggleButton ("toggleLSB"));
    toggleLSB->setButtonText ("LSB");
    toggleLSB->setConnectedEdges (Button::ConnectedOnRight);
    toggleLSB->addListener (this);

    addAndMakeVisible (toggleUSB = new ToggleButton ("toggleUSB"));
    toggleUSB->setButtonText ("USB");
    toggleUSB->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    toggleUSB->addListener (this);
    toggleUSB->setToggleState (true, false);

    addAndMakeVisible (toggleCW = new ToggleButton ("toggleCW"));
    toggleCW->setButtonText ("CW");
    toggleCW->setConnectedEdges (Button::ConnectedOnLeft);
    toggleCW->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	mLoFreq = 0.0;
	mTuneFreq = 0.0;
    //[/Constructor]
}

RadioPanel::~RadioPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    Spectrum = nullptr;
    label_freq = nullptr;
    label_lo_freq = nullptr;
    label_tune = nullptr;
    label_tune_freq = nullptr;
    next_band = nullptr;
    prev_band = nullptr;
    toggleLSB = nullptr;
    toggleUSB = nullptr;
    toggleCW = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RadioPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RadioPanel::resized()
{
    Spectrum->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.3328f));
    label_freq->setBounds (proportionOfWidth (0.0139f), proportionOfHeight (0.3594f), proportionOfWidth (0.1533f), proportionOfHeight (0.0399f));
    label_lo_freq->setBounds (proportionOfWidth (0.2230f), proportionOfHeight (0.3594f), proportionOfWidth (0.2091f), proportionOfHeight (0.0399f));
    label_tune->setBounds (proportionOfWidth (0.0139f), proportionOfHeight (0.4127f), proportionOfWidth (0.1812f), proportionOfHeight (0.0399f));
    label_tune_freq->setBounds (proportionOfWidth (0.2230f), proportionOfHeight (0.4127f), proportionOfWidth (0.2091f), proportionOfHeight (0.0399f));
    next_band->setBounds (proportionOfWidth (0.4739f), proportionOfHeight (0.3594f), proportionOfWidth (0.2613f), proportionOfHeight (0.0399f));
    prev_band->setBounds (proportionOfWidth (0.4739f), proportionOfHeight (0.4127f), proportionOfWidth (0.2613f), proportionOfHeight (0.0399f));
    toggleLSB->setBounds (24, 296, 72, 24);
    toggleUSB->setBounds (112, 296, 80, 24);
    toggleCW->setBounds (192, 296, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RadioPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == next_band)
    {
        //[UserButtonCode_next_band] -- add your button handler code here..
		CoreTimer::changeBand(1);
        //[/UserButtonCode_next_band]
    }
    else if (buttonThatWasClicked == prev_band)
    {
        //[UserButtonCode_prev_band] -- add your button handler code here..
		CoreTimer::changeBand(-1);
        //[/UserButtonCode_prev_band]
    }
    else if (buttonThatWasClicked == toggleLSB)
    {
        //[UserButtonCode_toggleLSB] -- add your button handler code here..
		toggleLSB->setToggleState(true, false);
		toggleUSB->setToggleState(false, false);
		toggleCW->setToggleState(false, false);
		CoreTimer::setModulation(CoreTimer::eLSB);
		//[/UserButtonCode_toggleLSB]
    }
    else if (buttonThatWasClicked == toggleUSB)
    {
        //[UserButtonCode_toggleUSB] -- add your button handler code here..
		toggleLSB->setToggleState(false, false);
		toggleUSB->setToggleState(true, false);
		toggleCW->setToggleState(false, false);
		CoreTimer::setModulation(CoreTimer::eUSB);
        //[/UserButtonCode_toggleUSB]
    }
    else if (buttonThatWasClicked == toggleCW)
    {
        //[UserButtonCode_toggleCW] -- add your button handler code here..
		toggleLSB->setToggleState(false, false);
		toggleUSB->setToggleState(false, false);
		toggleCW->setToggleState(true, false);
		CoreTimer::setModulation(CoreTimer::eCW);
        //[/UserButtonCode_toggleCW]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void  RadioPanel::handleAsyncUpdate ()
{
	char fs[32];
	snprintf(fs, 31, "%02.6f", mLoFreq);
	label_lo_freq->setText(fs, juce::sendNotification );
	snprintf(fs, 31, "%02.6f", mTuneFreq);
	label_tune_freq->setText(fs, juce::sendNotification );
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RadioPanel" componentName=""
                 parentClasses="public Component, public AsyncUpdater" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffd3d3d3"/>
  <GENERICCOMPONENT name="SpectrumScope" id="b343ab780f933c90" memberName="Spectrum"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 33.278%"
                    class="SpectrumScope" params=""/>
  <LABEL name="frequency" id="6a8a821458ed5a92" memberName="label_freq"
         virtualName="" explicitFocusOrder="0" pos="1.394% 35.94% 15.331% 3.993%"
         edTextCol="ff000000" edBkgCol="0" labelText="LO Frequency" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="new label" id="ce79911c4e45815" memberName="label_lo_freq"
         virtualName="" explicitFocusOrder="0" pos="22.3% 35.94% 20.906% 3.993%"
         bkgCol="ff44d01c" edTextCol="ff000000" edBkgCol="0" labelText="00.000000"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="18" bold="1" italic="0"
         justification="36"/>
  <LABEL name="new label" id="8816d45298b52045" memberName="label_tune"
         virtualName="" explicitFocusOrder="0" pos="1.394% 41.265% 18.118% 3.993%"
         edTextCol="ff000000" edBkgCol="0" labelText="Tune frequency"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="new label" id="f178cba21020c72a" memberName="label_tune_freq"
         virtualName="" explicitFocusOrder="0" pos="22.3% 41.265% 20.906% 3.993%"
         bkgCol="ff44d01c" edTextCol="ff000000" edBkgCol="0" labelText="00.000000"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="18" bold="1" italic="0"
         justification="36"/>
  <TEXTBUTTON name="new button" id="f9f491d913fc7eef" memberName="next_band"
              virtualName="" explicitFocusOrder="0" pos="47.387% 35.94% 26.132% 3.993%"
              buttonText="Band Up" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="239a76602259744b" memberName="prev_band"
              virtualName="" explicitFocusOrder="0" pos="47.387% 41.265% 26.132% 3.993%"
              buttonText="Band Down" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="toggleLSB" id="ce4fee1e53f274bb" memberName="toggleLSB"
                virtualName="" explicitFocusOrder="0" pos="24 296 72 24" buttonText="LSB"
                connectedEdges="2" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="toggleUSB" id="db936424075b37aa" memberName="toggleUSB"
                virtualName="" explicitFocusOrder="0" pos="112 296 80 24" buttonText="USB"
                connectedEdges="3" needsCallback="1" radioGroupId="0" state="1"/>
  <TOGGLEBUTTON name="toggleCW" id="ad4efec312bf3341" memberName="toggleCW" virtualName=""
                explicitFocusOrder="0" pos="192 296 96 24" buttonText="CW" connectedEdges="1"
                needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
