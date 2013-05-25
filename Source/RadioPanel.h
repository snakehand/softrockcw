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

#ifndef __JUCE_HEADER_3052D2EADD7DE9D6__
#define __JUCE_HEADER_3052D2EADD7DE9D6__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SpectrumScope.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RadioPanel  : public Component,
                    public AsyncUpdater,
                    public ButtonListener
{
public:
    //==============================================================================
    RadioPanel ();
    ~RadioPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setLoFreq(double f) {
		mLoFreq = f;
		triggerAsyncUpdate();
	}

	void setTuneFreq(double f) {
		mTuneFreq = f;
		triggerAsyncUpdate();
	}

	virtual void handleAsyncUpdate ();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	double mLoFreq;
	double mTuneFreq;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<SpectrumScope> Spectrum;
    ScopedPointer<Label> label_freq;
    ScopedPointer<Label> label_lo_freq;
    ScopedPointer<Label> label_tune;
    ScopedPointer<Label> label_tune_freq;
    ScopedPointer<TextButton> next_band;
    ScopedPointer<TextButton> prev_band;
    ScopedPointer<ToggleButton> toggleLSB;
    ScopedPointer<ToggleButton> toggleUSB;
    ScopedPointer<ToggleButton> toggleCW;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3052D2EADD7DE9D6__
