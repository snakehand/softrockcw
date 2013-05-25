/*
  ==============================================================================

    Waterfall.cpp
    Created: 13 May 2013 11:11:57pm
    Author:  frank

  ==============================================================================
*/

#include "Waterfall.h"
#include "SpectrumScope.h"
#include <math.h>

#define FFT_SIZE 16384


Waterfall::Waterfall() :
	mState(0)
{
	mFftCfg = kiss_fft_alloc(FFT_SIZE,0,NULL,NULL);
	mInput = new kiss_fft_cpx[FFT_SIZE];
	mOutput = new kiss_fft_cpx[FFT_SIZE];
	startTimer(130);
}

Waterfall::~Waterfall()
{
	delete mInput;
	delete mOutput;
}

void Waterfall::pushSamples(float *i_samples, float *q_samples, int num_samples)
{
	if (mState==1) {
		int todo = num_samples;
		int available = FFT_SIZE - mPos;
		if (todo>available) {
			todo = available;
		}
		for (int i=0; i<todo; i++) {
			mInput[mPos].r = q_samples[i];
			mInput[mPos].i = i_samples[i];
			mPos++;
		}
		if (mPos>=FFT_SIZE) {
			mState = 2;
		}
	}
}

void Waterfall::hiResTimerCallback()
{
	switch (mState) {
	default:
	case 0:
		mPos = 0;
		mState = 1;
		break;
	case 1:
		break;
	case 2:
		kiss_fft(mFftCfg, mInput, mOutput);
		SpectrumScope *scope = SpectrumScope::GetInstance(0);
		if (scope) {
			float *val = scope->getValues();
			int binsize = FFT_SIZE / 1024;
			float v = 0.0f;
			int pos = 0;
			int outpos = 0;
			for (int i=0; i<FFT_SIZE; i++) {
				float x = mOutput[i].r;
				float y = mOutput[i].i;
				v += sqrtf(x*x+y*y);
				if (++pos>=binsize) {
					v = v * (1024.0f / (float)FFT_SIZE);
					float old = val[outpos];
					if (!((old<0.0f)&&(old>-200.0f))) {
						// Catch -NAN
						old = 0.0f;
					}
					val[outpos++] = 0.25f*old + 0.75f*log(v) * 4.3429448190325175f;
					v = 0.0f;
					pos = 0;
				}
			}
			scope->update();
		}
		mPos = 0;
		mState = 1;
		break;
	}
}
