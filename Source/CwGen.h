/*
  ==============================================================================

    CwGen.h
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#ifndef CW_GEN_H
#define CW_GEN_H

#include <string>

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
	void queueText(std::string txt);

private:
	enum KeyState {
		eOff,
		eRising,
		eOn,
		eFalling
	};

	enum KeyMode {
		eStraight,
		ePaddle
	};

	enum PaddleState {
		eDit,
		eDah,
		ePause
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
};

#if 0
class CwModulator : public Tickable {
public:
	CwModulator(CwGen *generator);
	~CwModulator();

	void setFreq(double f);

	void Tick();

	Pipe* getPipe() {return &mPipe;}
private:
	Pipe  mPipe;
	CwGen* mGen;
	double mFreq;
	double mPos;
	float *mData;
};
#endif

#endif