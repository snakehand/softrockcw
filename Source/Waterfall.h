/*
  ==============================================================================

    Waterfall.h
    Created: 13 May 2013 11:11:57pm
    Author:  frank

  ==============================================================================
*/

#ifndef __WATERFALL_H_BBB49867__
#define __WATERFALL_H_BBB49867__

#include "JuceHeader.h"
#include "kiss_fft130/kiss_fft.h"

class Waterfall  : public HighResolutionTimer {
public:
	Waterfall();
	~Waterfall();

	void pushSamples(float *i_samples, float *q_samples, int num_samples);
    virtual void hiResTimerCallback();

private:
	kiss_fft_cfg mFftCfg;

	volatile int mState;
	volatile int mPos;

	kiss_fft_cpx *mInput;
	kiss_fft_cpx *mOutput;
};


#endif  // __WATERFALL_H_BBB49867__
