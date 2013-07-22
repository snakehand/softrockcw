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
#include "RadioPanel.h"
#include "RxSettings.h"
#include "TxSettings.h"
#include "AudioPath.h"
//[/Headers]

#include "MainTabs.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainTabs::MainTabs ()
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (30);
    tabbedComponent->addTab ("Tuner", Colours::lightgrey, new RadioPanel(), true);
    tabbedComponent->addTab ("RX Audio", Colours::lightgrey, new RxSettings(), true);
    tabbedComponent->addTab ("TX Audio", Colours::lightgrey, new TxSettings(), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 640);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainTabs::~MainTabs()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainTabs::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainTabs::resized()
{
    tabbedComponent->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

bool MainTabs::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	char ch = (char)key.getTextCharacter();
	int n = CoreTimer::insertCW((char)toupper(ch));
    if (n) {
        return true; // Return true if your handler uses this key event, or false to allow it to be passed-on.
    }
	return Component::keyPressed(key);
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainTabs::addComponent(const String &tabName, const Colour &tabBackgroundColour, Component *contentComponent)
{
	tabbedComponent->addTab(tabName,tabBackgroundColour,contentComponent,true);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainTabs" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="800" initialHeight="640">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="7450ded85c1255cc" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="Tuner" colour="ffd3d3d3" useJucerComp="0" contentClassName="RadioPanel"
         constructorParams="" jucerComponentFile="RadioPanel.cpp"/>
    <TAB name="RX Audio" colour="ffd3d3d3" useJucerComp="0" contentClassName="RxSettings"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="TX Audio" colour="ffd3d3d3" useJucerComp="0" contentClassName="TxSettings"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
