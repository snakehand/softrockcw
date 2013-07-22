/*
  ==============================================================================

    CwGen.h
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#ifndef CW_GEN_H
#define CW_GEN_H

#include <string>
#include <deque>
#include "../JuceLibraryCode/JuceHeader.h"

class CwGen {
public:
	CwGen();
	~CwGen();

	void setWPM(float wpm);
	void setSampleRate(int rate);

	float getEnvelopeSample();
	float getLastSample() {return mLastSample;}

	void setPaddleState(int paddle);
	void setKeyState(bool key);
	int queueText(std::string txt);

private:
	enum KeyState {
		eOff,
		eRising,
		eOn,
		eFalling
	};

	enum KeyMode {
		eStraight,
		ePaddle,
		eSequence
	};

	enum PaddleState {
		eDit,
		eDah,
		ePause
	};

	enum Segment {
		eNone,
		eShortOn,
		eLongOn,
		eShortOff,
		eLongOff
	};

	void calcTable();

	float   mWPM;
	int     mSampleRate;
	double *mRiseTable;
	int 	mRiseTableSize;

	int mPos;
	KeyState mKeyState;
	bool mStraightKey;
	KeyMode mMode;
	int mPaddle;
	int mDuration;
	PaddleState mPaddleState;
	PaddleState mPrevState;
	float mLastSample;
	int mPaddleDebounceA;
	int mPaddleDebounceB;
	int mLastPaddle;

	std::deque<Segment> mSegmentDeck;
	CriticalSection mMutex;
};

#endif