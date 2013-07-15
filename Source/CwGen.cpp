/*
  ==============================================================================

    CwGen.cpp
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#include "CwGen.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

static double blackman_harris(double x)
{
	double a0 = 0.35875;
	double a1 = 0.48829;
	double a2 = 0.14128;
	double a3 = 0.01168;
	double seg1 = a1 * cos(2.0*M_PI*x);
	double seg2 = a2 * cos(4.0*M_PI*x);
	double seg3 = a3 * cos(6.0*M_PI*x);

	return a0 - seg1 + seg2 - seg3;
}

CwGen::CwGen() :
	mWPM(20),
	mSampleRate(44100),
	mRiseTable(0),
	mRiseTableSize(0),
	mPos(0),
	mKeyState(eOff),
	mStraightKey(false),
	mMode(eStraight),
	mPaddle(0),
	mDuration(0),
	mPaddleState(ePause),
	mPrevState(ePause),
	mLastSample(0.0f),
	mPaddleDebounceA(0),
	mPaddleDebounceB(0),
	mLastPaddle(0)
{
	calcTable();
}

CwGen::~CwGen()
{
	delete [] mRiseTable;
}

void CwGen::setWPM(float wpm)
{
	mWPM = wpm;
	calcTable();
}

void CwGen::setSampleRate(int rate)
{
	mSampleRate = rate;
	calcTable();
}

void CwGen::calcTable()
{
	double risetime = 0.005; // 5ms
	mRiseTableSize = (int)((double)mSampleRate*risetime*2.7);
	if (mRiseTableSize==0) {
		mRiseTableSize = 1;
	}
	delete [] mRiseTable;
	mRiseTable = new double[mRiseTableSize];

	/* Create impulse response */
	double f = 1.0/((double)mRiseTableSize-1.0);
	for (int i=0; i<mRiseTableSize ; i++) {
		mRiseTable[i] = blackman_harris(f*(double)i);
	}

	/* integrate to create step response */
	double sum = 0.0;
	for (int i=0; i<mRiseTableSize ; i++) {
		sum +=	mRiseTable[i];
		mRiseTable[i] = sum;
	}

	/* normalize step response */
	for (int i=0; i<mRiseTableSize ; i++) {
		mRiseTable[i] = mRiseTable[i] / sum;
		// printf("%f\n", mRiseTable[i]);
	}

}


float CwGen::getEnvelopeSample()
{
	float res = 0.0f;
	if (mPaddleDebounceA < 0) {
		mPaddleDebounceA++;
	}
	if (mPaddleDebounceB < 0) {
		mPaddleDebounceB++;
	}
	switch (mKeyState) {
	case eOff:
		if (!mStraightKey) break;
		mPos = 0;
		mKeyState = eRising;
		// Fall through
	case eRising:
		res = (float)mRiseTable[mPos++];
		if (mPos>=mRiseTableSize) {
			mKeyState = eOn;
		}
		break;
	case eOn:
		res = 1.0;
		if (mStraightKey) break;
		mPos = mRiseTableSize-1;
		mKeyState = eFalling;
		// Fall through
	case eFalling:
		res = (float)mRiseTable[mPos--];
		if (mPos<0) {
			mKeyState = eOff;
		}
		break;
	}
	mLastSample = res;

	/* Update paddle state */
	if ((mMode==ePaddle) && (--mDuration<0)) {
		mPaddle = 0;
		if (mPaddleDebounceA > 0) {
			mPaddle |= 0x1;
		}
		if (mPaddleDebounceB > 0) {
			mPaddle |= 0x2;
		}
		switch (mPaddle&0x03) {
		case 0x00:
			mPrevState = eDah;
			mPaddleState = ePause;
			break;
		case 0x01:
			switch (mPaddleState) {
			case eDit:
			case eDah:
				mPaddleState = ePause;
				break;
			case ePause:
				mPaddleState = eDit;
				break;
			}
			break;
		case 0x02:
			switch (mPaddleState) {
			case eDit:
			case eDah:
				mPaddleState = ePause;
				break;
			case ePause:
				mPaddleState = eDah;
				break;
			}
			break;
		case 0x03:
			switch (mPaddleState) {
			case eDah:
			case eDit:
				mPaddleState = ePause;
				break;
			case ePause:
				if (mPrevState==eDah) {
					mPaddleState = eDit;
				} else {
					mPaddleState = eDah;
				}
				break;
			}
		}

		if (mPaddleState!=ePause) {
			mPrevState = mPaddleState;
		}

		switch (mPaddleState) {
		case eDit:
			mDuration = 3000;
			mStraightKey = true;
			mPaddleDebounceA = -1500;
			mPaddleDebounceB = -1000;
			break;
		case eDah:
			mDuration = 9000;
			mStraightKey = true;
			mPaddleDebounceA = -1000;
			mPaddleDebounceB = -4500;
			break;
		case ePause:
			mDuration = 3000;
			mStraightKey = false;
			break;
		}
	}

	return res;
}

void CwGen::setPaddleState(int paddle)
{
	int debounce = 1;
	if (paddle && (mLastPaddle== 0) && (mPaddleState==ePause)) {
		mDuration = 0;  // Abort pause
	}
	if (1) {
		// Swap
		if ((paddle&0x2) && (mPaddleDebounceA>=0)) {
			mPaddleDebounceA = debounce;
		}
		if ((paddle&0x1) && (mPaddleDebounceB>=0)) {
			mPaddleDebounceB = debounce;
		}
	} else {
		if (paddle&0x1) mPaddleDebounceA = debounce;
		if (paddle&0x2) mPaddleDebounceB = debounce;
	}

	mLastPaddle = paddle;
	mMode = ePaddle;
}

void CwGen::setKeyState(bool key)
{
	mStraightKey = key;
	mMode = eStraight;
}

void CwGen::queueText(std::string txt)
{
}
