/*
  ==============================================================================

    Receiver.cpp
    Created: 12 May 2013 1:09:20pm
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#include <math.h>
#include <string.h>
#include "Receiver.h"
#include "remez\remez.h"
#include "SpectrumScope.h"

static void wrap_remez(int m, float fc, float *taps)
{
	double* t = new double[m];
	double bands[4];
	double desired[2];
	double weights[2];

	bands[0] = 0.0;
	bands[1] = (double)fc;
	bands[2] = 1.25*(double)fc;
	bands[3] = 0.5;

	desired[0] = 1.0;
	desired[1] = 0.0;

	weights[0] = 1;
	weights[1] = 10;

	remez(t, m, 2, bands, desired, weights, BANDPASS);
	double dsum = 0.0;
	for (int i=0; i<m; i++)
	{
		dsum+=t[i];
	}
	float fsum = (float)dsum;
	for (int i=0; i<m; i++)
	{
		taps[i] = (float)t[i] / fsum;
	}
	delete [] t;
}



Receiver::Receiver() :
	mLow(10000.0),
	mHigh(14000.0),
	mOffset(0.0),
	mRateIn(48000),
	mRateOut(48000),
	mWorking(false),
	mFCoff1(0),
	mWorkI(0),
	mWorkQ(0),
	mAgc(1.0),
	mSampleTick(0)
{
	setup();
}

Receiver::~Receiver()
{
	delete mFCoff1;
	delete mWorkI;
	delete mWorkQ;
}

void Receiver::setInputSamplerate(int rate)
{
	if (mRateIn==rate) {
		return;
	}
	mRateIn = rate;
	setup();
}

void Receiver::setOutputSamplerate(int rate)
{
	if (mRateOut==rate) {
		return;
	}
	mRateOut = rate;
	setup();
}

void Receiver::setWindow(double low, double high, double off)
{
	mLow = low;
	mHigh = high;
	mOffset = off;
	setupPhasor();
}

void Receiver::pushSamples(float *i_samples, float *q_samples, int num_samples)
{
	if (!mWorking) {
		return;
	}
	for (int i=0; i<num_samples; i++) {
		float bx = (float)sin(-mPhasorPos);
		float by = (float)cos(-mPhasorPos);
		float ax = i_samples[i];
		float ay = q_samples[i];
		mWorkI[mRingPos] = ax*bx - ay*by;
		mWorkQ[mRingPos] = ax*by + ay*bx;
		mRingPos++;
		mPhasorPos += mPhasorPosDelta;
		while (mPhasorPos > 6.283185307179586) {
			mPhasorPos -= 6.283185307179586;
		}
		if (mRingPos>=mFilterSize1) {
			mRingPos = 0;
		}
		mSampleTick++;
		if (mSampleTick<mDecimate) {
			continue;
		}
		mSampleTick = 0;
		float ri = 0.0;
		float rq = 0.0;
		int offset = mFilterSize1 - mRingPos;
		for (int j = 0; j<mFilterSize1; j++) {
			ri += mWorkI[j] * mFCoff1[offset+j];
			rq += mWorkQ[j] * mFCoff1[offset+j];
		}
		bx = (float)sin(mPhasorOutPos);
		by = (float)cos(mPhasorOutPos);
		ax = ri;
		ay = rq;
		ri = ax*bx - ay*by;
		// rq = ax*by + ay*bx;
		mOutput.push_back(ri);
		mPhasorOutPos += mPhasorOutPosDelta;
		while (mPhasorOutPos > 6.283185307179586) {
			mPhasorOutPos -= 6.283185307179586;
		}
	}
}

int  Receiver::getNumReadySamples()
{
	return mOutput.size();
}

int Receiver::getSamples(float *samples, int num)
{
	int ready = mOutput.size();
	if (ready>num) {
		ready = num;
	}
	for (int i=0; i<ready; i++) {
		float sample = mOutput.front() * mAgc;
		if (sample*sample>0.125f) {
			mAgc = mAgc * 0.99f;
		} else {
			mAgc += 0.001f;
		}
		samples[i] = sample;
		mOutput.pop_front();
	}
	return ready;
}


void Receiver::setup()
{
	// Check if resampling is other than 1,2,4
	mWorking = true;
	mInterpolate = 1;
	mDecimate = 1;
	if (mRateIn!=mRateOut) {
		int low;
		int high;
		if (mRateIn<mRateOut) {
			low = mRateIn;
			high = mRateOut;
		} else {
			high = mRateIn;
			low = mRateOut;
		}
		if ((2*low!=high)&&(4*low!=high)) {
			// can't resample
			mWorking = false;
			return;
		}
		int factor = high / low;
		if (mRateIn<mRateOut) {
			mInterpolate = factor;
		} else {
			mDecimate = factor;
		}
	}

	delete mFCoff1;
	delete mWorkI;
	delete mWorkQ;

	mFilterSize1 = 101;
	float width = (float)(abs(mLow-mHigh)/(2.0*(double)mRateIn));
	mFCoff1 = new float[mFilterSize1*2];
	mWorkI = new float[mFilterSize1];
	mWorkQ = new float[mFilterSize1];
	wrap_remez(mFilterSize1,1.0f*width,mFCoff1); // BUG: 1.5 - fudge factor 
	memcpy(&mFCoff1[mFilterSize1],mFCoff1,mFilterSize1*sizeof(float));
	memset(mWorkI,0,mFilterSize1*sizeof(float));
	memset(mWorkQ,0,mFilterSize1*sizeof(float));
	setupPhasor();
}

void Receiver::setupPhasor()
{
	float width = (float)(abs(mLow-mHigh)/(2.0*(double)mRateIn));
	mRingPos = 0;
	mPhasorPos = 0.0;
    mPhasorPosDelta = ((mLow+mHigh)*3.1415926535) / (double)mRateIn;
	mPhasorOutPos = 0.0;
	double off = mOffset / (double)mRateIn;
	if (mLow<mHigh) {
	    mPhasorOutPosDelta = (width+off)*6.283185307179586*mDecimate;
	} else {
	    mPhasorOutPosDelta = (-width+off)*6.283185307179586*mDecimate;
	}

	if (mPhasorPosDelta<0.0) {
		mPhasorPosDelta += 6.283185307179586;
	}
	if (mPhasorOutPosDelta<0.0) {
		mPhasorOutPosDelta += 6.283185307179586;
	}

	SpectrumScope *scope = SpectrumScope::GetInstance(0);

	if (scope) {
		float x1 = (float)mLow / (float)mRateIn;
		float x2 = (float)mHigh / (float)mRateIn;
		scope->markRegion(x1+0.5f,x2+0.5f);
	}

}
