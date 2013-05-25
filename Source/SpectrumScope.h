/*
  ==============================================================================

    SpectrumScope.h
    Created: 14 May 2013 5:45:18pm
    Author:  frank

  ==============================================================================
*/

#ifndef __SPECTRUMSCOPE_H_BBD53298__
#define __SPECTRUMSCOPE_H_BBD53298__

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SpectrumScope    : public Component, public AsyncUpdater
{
public:
    SpectrumScope();
    ~SpectrumScope();

    void paint (Graphics&);
    void resized();

	void update();
	static SpectrumScope* GetInstance(int i);
	float* getValues() { return mValues; }
	void markRegion(float a, float b);

	virtual void handleAsyncUpdate ();
	virtual void mouseDown(const MouseEvent &event);
	virtual void mouseDrag (const MouseEvent &event);
	virtual void mouseUp (const MouseEvent &event);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumScope)
    
	ScopedPointer<Image> image;
	float mValues[1024];
	static SpectrumScope* mInstances[10];
	float mRegionA;
	float mRegionB;

};


#endif  // __SPECTRUMSCOPE_H_BBD53298__
