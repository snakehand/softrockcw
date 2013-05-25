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
//[/Headers]

#include "TxSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TxSettings::TxSettings ()
{
    addAndMakeVisible (sliderTxLevel = new Slider ("sliderTxLevel"));
    sliderTxLevel->setRange (-100, 0, 0);
    sliderTxLevel->setSliderStyle (Slider::LinearHorizontal);
    sliderTxLevel->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderTxLevel->addListener (this);

    addAndMakeVisible (labelTxLevel = new Label ("labelTxLevel",
                                                 "Tx level (dB)"));
    labelTxLevel->setFont (Font (15.00f, Font::plain));
    labelTxLevel->setJustificationType (Justification::centredLeft);
    labelTxLevel->setEditable (false, false, false);
    labelTxLevel->setColour (TextEditor::textColourId, Colours::black);
    labelTxLevel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelTxBalance = new Label ("labelTxBalance",
                                                   "Tx balance"));
    labelTxBalance->setFont (Font (15.00f, Font::plain));
    labelTxBalance->setJustificationType (Justification::centredLeft);
    labelTxBalance->setEditable (false, false, false);
    labelTxBalance->setColour (TextEditor::textColourId, Colours::black);
    labelTxBalance->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderTxBalance = new Slider ("sliderTxBalance"));
    sliderTxBalance->setRange (-50, 50, 0);
    sliderTxBalance->setSliderStyle (Slider::LinearHorizontal);
    sliderTxBalance->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderTxBalance->addListener (this);

    addAndMakeVisible (labelWPM = new Label ("labelWPM",
                                             "Keyer WPM"));
    labelWPM->setFont (Font (15.00f, Font::bold));
    labelWPM->setJustificationType (Justification::centredLeft);
    labelWPM->setEditable (false, false, false);
    labelWPM->setColour (TextEditor::textColourId, Colours::black);
    labelWPM->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textWPM = new TextEditor ("textWPM"));
    textWPM->setMultiLine (false);
    textWPM->setReturnKeyStartsNewLine (false);
    textWPM->setReadOnly (false);
    textWPM->setScrollbarsShown (true);
    textWPM->setCaretVisible (true);
    textWPM->setPopupMenuEnabled (true);
    textWPM->setText ("20");

    addAndMakeVisible (toggleStraightKey = new ToggleButton ("toggleStraightKey"));
    toggleStraightKey->setButtonText ("Straight key");
    toggleStraightKey->addListener (this);

    addAndMakeVisible (toggleReversePaddle = new ToggleButton ("toggleReversePaddle"));
    toggleReversePaddle->setButtonText ("Reverse Paddle");
    toggleReversePaddle->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TxSettings::~TxSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderTxLevel = nullptr;
    labelTxLevel = nullptr;
    labelTxBalance = nullptr;
    sliderTxBalance = nullptr;
    labelWPM = nullptr;
    textWPM = nullptr;
    toggleStraightKey = nullptr;
    toggleReversePaddle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TxSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TxSettings::resized()
{
    sliderTxLevel->setBounds (144, 32, proportionOfWidth (0.7108f), 24);
    labelTxLevel->setBounds (16, 32, 104, 24);
    labelTxBalance->setBounds (16, 88, 104, 24);
    sliderTxBalance->setBounds (144, 88, proportionOfWidth (0.7247f), 24);
    labelWPM->setBounds (16, 144, 120, 24);
    textWPM->setBounds (128, 144, 71, 24);
    toggleStraightKey->setBounds (24, 192, 128, 24);
    toggleReversePaddle->setBounds (152, 192, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TxSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderTxLevel)
    {
        //[UserSliderCode_sliderTxLevel] -- add your slider handling code here..
        //[/UserSliderCode_sliderTxLevel]
    }
    else if (sliderThatWasMoved == sliderTxBalance)
    {
        //[UserSliderCode_sliderTxBalance] -- add your slider handling code here..
        //[/UserSliderCode_sliderTxBalance]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void TxSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleStraightKey)
    {
        //[UserButtonCode_toggleStraightKey] -- add your button handler code here..
        //[/UserButtonCode_toggleStraightKey]
    }
    else if (buttonThatWasClicked == toggleReversePaddle)
    {
        //[UserButtonCode_toggleReversePaddle] -- add your button handler code here..
        //[/UserButtonCode_toggleReversePaddle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TxSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffd3d3d3"/>
  <SLIDER name="sliderTxLevel" id="312eb3cc3e83a570" memberName="sliderTxLevel"
          virtualName="" explicitFocusOrder="0" pos="144 32 71.08% 24"
          min="-100" max="0" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="labelTxLevel" id="108fa66ebd8bf7ec" memberName="labelTxLevel"
         virtualName="" explicitFocusOrder="0" pos="16 32 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tx level (dB)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="labelTxBalance" id="9ed26cfa4c4cdc11" memberName="labelTxBalance"
         virtualName="" explicitFocusOrder="0" pos="16 88 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tx balance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="sliderTxBalance" id="8baaa62d19ea79f8" memberName="sliderTxBalance"
          virtualName="" explicitFocusOrder="0" pos="144 88 72.474% 24"
          min="-50" max="50" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="labelWPM" id="d34eb4b85228a1ae" memberName="labelWPM" virtualName=""
         explicitFocusOrder="0" pos="16 144 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Keyer WPM" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="33"/>
  <TEXTEDITOR name="textWPM" id="9530ee50fd2b1487" memberName="textWPM" virtualName=""
              explicitFocusOrder="0" pos="128 144 71 24" initialText="20" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="toggleStraightKey" id="a6537873b6660c95" memberName="toggleStraightKey"
                virtualName="" explicitFocusOrder="0" pos="24 192 128 24" buttonText="Straight key"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="toggleReversePaddle" id="774647cb596dec3b" memberName="toggleReversePaddle"
                virtualName="" explicitFocusOrder="0" pos="152 192 150 24" buttonText="Reverse Paddle"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
