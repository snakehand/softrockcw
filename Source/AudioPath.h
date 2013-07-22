/*
  ==============================================================================

    AudioPath.h
    Created: 10 May 2013 8:33:59pm
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#ifndef __AUDIOPATH_H_9CCE1A30__
#define __AUDIOPATH_H_9CCE1A30__
#include "JuceHeader.h"
#include "HardRock.h"
#include "RadioPanel.h"

void initAudio();
void deinitAudio();
AudioDeviceSelectorComponent* getAudioSelector(int num);


class CoreTimer : public HighResolutionTimer 
{
public:
	CoreTimer(HardRock *radio, RadioPanel *panel);
	virtual	~CoreTimer();

    virtual void hiResTimerCallback();

	static void setTuneOffset(float o) { mTuneOffset = o; }
	static void retune() {mRetune = true;};
	static void changeBand(int o) { mBandChange = o; }

	enum modulation {
		eLSB,
		eUSB,
		eCW
	};

	static modulation getCurrentMod() { return mCurrentMod; }

	static void setModulation(modulation mod);
	static void tuneReciever(int num, float freq);
	static void setCWfreq(float f) {mCWfreq=f;}
	static void setChannelSwap(bool swap);
	static int insertCW(char ch);

private:
	HardRock *mRadio;
	RadioPanel *mPanel;
	int mNumTicks;
	double mTuneStart;
	static float mTuneOffset;
	static bool mRetune;
	static int mBandChange;
	static modulation mCurrentMod;
	static float mCWfreq;

};

#endif  // __AUDIOPATH_H_9CCE1A30__

