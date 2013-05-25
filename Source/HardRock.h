/*
  ==============================================================================

    HardRock.h
    Created: 12 May 2013 10:32:18am
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#ifndef __HARDROCK_H_E65753AF__
#define __HARDROCK_H_E65753AF__

#include "JuceHeader.h"

class HardRock {
public:
	HardRock();
	~HardRock();

	bool setLO(double freq);
	double getLO();

	// Read CW key, with bit field
	// 0x04 - CW key supported
	// 0x02 - key 1
	// 0x01 - key 2
	int  readKey();

	float getWidth() { return mWidth; }
	void setWidth(float w) { mWidth=w; }

private:
	DynamicLibrary mLib;
	bool mConnected;
	float mWidth;
};

#endif  // __HARDROCK_H_E65753AF__
