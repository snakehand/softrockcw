/*
  ==============================================================================

    Receiver.h
    Created: 12 May 2013 1:09:20pm
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#ifndef __RECEIVER_H_89F32EE__
#define __RECEIVER_H_89F32EE__

#include <deque>

class Receiver {
public:
	Receiver();
	~Receiver();

	void setInputSamplerate(int rate);
	void setOutputSamplerate(int rate);

	void setWindow(double low, double high, double off);

	void pushSamples(float *i_samples, float *q_samples, int num_samples);
	int  getNumReadySamples();
	int  getSamples(float *samples, int num);

	double getTuned() { return mLow / 1000000.0; }
	int getRateIn() { return mRateIn; }

private:
	void setup();
	void setupPhasor();

	double mLow;
	double mHigh;
	double mOffset;
	int mRateIn;
	int mRateOut;
	int mInterpolate;
	int mDecimate;

	bool mWorking;

	float *mFCoff1;
	int mFilterSize1;

	float *mWorkI;
	float *mWorkQ;
	int mRingPos;

	double mPhasorPos;
	double mPhasorPosDelta;

	double mPhasorOutPos;
	double mPhasorOutPosDelta;

	std::deque<float> mOutput;
	float mAgc;

	int mSampleTick;
};


#endif  // __RECEIVER_H_89F32EE__
