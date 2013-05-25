/*
  ==============================================================================

    SpectrumScope.cpp
    Created: 14 May 2013 5:45:18pm
    Author:  frank

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectrumScope.h"
#include "AudioPath.h"

SpectrumScope* SpectrumScope::mInstances[10] = {0,0,0,0,0,0,0,0,0,0};

SpectrumScope* SpectrumScope::GetInstance(int i)
{
	if ((i<0)||(i>9)) {
		return 0;
	}
	return mInstances[0];
}

//==============================================================================
SpectrumScope::SpectrumScope() :
	mRegionA(0.0f),
	mRegionB(0.0f)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	if (getWidth() && getHeight()) {
		image = new Image(Image::ARGB,getWidth(), getHeight(), true);
	} else {
		image = 0;
	}
	memset(mValues,0,sizeof(mValues));
	mInstances[0] = this;
}

SpectrumScope::~SpectrumScope()
{
	mInstances[0] = 0;
	image = 0;
}

void SpectrumScope::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
	int w = getWidth();
	int h = getHeight();
	if (image) {
		g.drawImage(*image,0,0,w,h,0,0,w,h);
	}

	if (mRegionA!=mRegionB) {
		g.setColour (Colours::grey);
		g.setOpacity(0.5f);
		g.fillRect (w*mRegionA,0.0f,w*(mRegionB - mRegionA),(float)h);
	}

#if 0
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("SpectrumScope", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
#endif
}

void SpectrumScope::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
	if (getWidth() && getHeight()) {
		image = new Image(Image::ARGB,getWidth(), getHeight(), true);
		image->setPixelAt(100,100,juce::Colour(0,0,0));
	} else {
		image = 0;
	}
}

void SpectrumScope::update()
{
	int w = getWidth();
	int h = getHeight();
	if (image && w && h) {
		image->moveImageSection(0,0,0,1,w,h-1);
		float x = 0.0;
		float d = 1024.0f/(float)w;
		for (int i=0; i<w; i++) {
			int p = ((int)x + 512)&0x3ff;
			int v = 768 + (int)(60.0f*mValues[p]);
			int r = 255;
			int g = 0;
			int b = 0;

			if (v<768) {
				r = 1024 - v;
				if (r<0) {
					r = 0;
				}
				g = 512 - v;
				if (g<0) {
					g = -g;
				}
				g = 256 - g;
				if (g<0) {
					g = 0;
				}
				if (v<512) {
					b = 255 - v / 2;
					if (b>255) {
						b=255;
					}
				}
			}

			image->setPixelAt(i,h-1,juce::Colour((juce::uint8)r,(juce::uint8)g,(juce::uint8)b));
			x += d;
		}
		triggerAsyncUpdate();
	}
}

void SpectrumScope::handleAsyncUpdate()
{
	repaint();
}

void SpectrumScope::mouseDown(const MouseEvent &event)
{
	if (event.mods.isLeftButtonDown()) {
		float w = (float)getWidth();
		float freq = 2.0f*(float)event.x / w - 1.0f;
		CoreTimer::tuneReciever(0,freq);
	}
}

void SpectrumScope::mouseDrag (const MouseEvent &event)
{
	if (event.mods.isRightButtonDown()) {
		int dist = event.getDistanceFromDragStartX();
		float offset = (float)dist / (float)getWidth();
		CoreTimer::setTuneOffset(-offset);
	}
}

void SpectrumScope::mouseUp (const MouseEvent &event)
{
	if (event.mods.isRightButtonDown()) {
		mouseDrag(event);
		CoreTimer::retune();
	}
}

void SpectrumScope::markRegion(float a, float b)
{
	if (a>b) {
		mRegionA = b;
		mRegionB = a;
	} else {
		mRegionA = a;
		mRegionB = b;
	}
}
