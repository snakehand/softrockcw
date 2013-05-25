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
#include "AudioPath.h"
//[/Headers]

#include "RxSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RxSettings::RxSettings ()
{
    addAndMakeVisible (swapButton = new ToggleButton ("swapIQ"));
    swapButton->setButtonText ("Swap I/Q");
    swapButton->addListener (this);

    addAndMakeVisible (RxBalance = new Slider ("RxBalance"));
    RxBalance->setRange (-50, 50, 0);
    RxBalance->setSliderStyle (Slider::LinearHorizontal);
    RxBalance->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    RxBalance->addListener (this);

    addAndMakeVisible (labelRxBalance = new Label ("labelRxBalance",
                                                   "Rx Balance"));
    labelRxBalance->setFont (Font (15.00f, Font::plain));
    labelRxBalance->setJustificationType (Justification::centredLeft);
    labelRxBalance->setEditable (false, false, false);
    labelRxBalance->setColour (TextEditor::textColourId, Colours::black);
    labelRxBalance->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          "CW pitch"));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (500, 1000, 50);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

RxSettings::~RxSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    swapButton = nullptr;
    RxBalance = nullptr;
    labelRxBalance = nullptr;
    label = nullptr;
    slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RxSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::lightgrey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RxSettings::resized()
{
    swapButton->setBounds (proportionOfWidth (0.0418f), proportionOfHeight (0.0399f), 150, 24);
    RxBalance->setBounds (128, 72, proportionOfWidth (0.7387f), 24);
    labelRxBalance->setBounds (16, 72, 96, 24);
    label->setBounds (16, 120, 104, 24);
    slider->setBounds (128, 120, proportionOfWidth (0.7387f), 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RxSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == swapButton)
    {
        //[UserButtonCode_swapButton] -- add your button handler code here..
		CoreTimer::setChannelSwap(swapButton->getToggleState());
        //[/UserButtonCode_swapButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void RxSettings::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == RxBalance)
    {
        //[UserSliderCode_RxBalance] -- add your slider handling code here..
        //[/UserSliderCode_RxBalance]
    }
    else if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
		CoreTimer::setCWfreq((float)slider->getValue());
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RxSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffd3d3d3"/>
  <TOGGLEBUTTON name="swapIQ" id="bfce0a6f8d36272" memberName="swapButton" virtualName=""
                explicitFocusOrder="0" pos="4.181% 3.993% 150 24" buttonText="Swap I/Q"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="RxBalance" id="2fc07ab6815a8aac" memberName="RxBalance"
          virtualName="" explicitFocusOrder="0" pos="128 72 73.868% 24"
          min="-50" max="50" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="labelRxBalance" id="25c26c7dcf2463cf" memberName="labelRxBalance"
         virtualName="" explicitFocusOrder="0" pos="16 72 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rx Balance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2510fd638b51d1be" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 120 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="CW pitch" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="57bec0a0418e7eb6" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="128 120 73.868% 24" min="500" max="1000"
          int="50" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
