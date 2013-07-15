/*
  ==============================================================================

    HardRock.cpp
    Created: 12 May 2013 10:32:19am
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#include "HardRock.h"
#include "SRDLL.h"


HardRock::HardRock()
{
#ifdef WIN32
	mConnected = mLib.open("SRDLL.dll");
	void *res = NULL;
	if (mConnected) {
		srOpen = (srOpen_t)mLib.getFunction("srOpen");
		res = srOpen(0x16C0, 0x05DC, NULL, NULL, NULL, -1);
		srSetFreq = (srSetFreq_t)mLib.getFunction("srSetFreq");
		srGetFreq = (srGetFreq_t)mLib.getFunction("srGetFreq");
		srGetCWInp = (srGetCWInp_t)mLib.getFunction("srGetCWInp");
	}
	if (res==NULL) {
		mConnected = false;
	}
#else
    mConnected = false;
#endif
}

HardRock::~HardRock()
{
#ifdef WIN32
	mLib.close();
#endif
}

bool HardRock::setLO(double freq)
{
#ifdef WIN32
	if (mConnected) {
		return srSetFreq(4.0*freq, 0x55) != 0;
	}
#endif
	return false;
}

double HardRock::getLO()
{
#ifdef WIN32
	if (mConnected) {
		double res = 0.0f;
		bool status = srGetFreq(&res);
		if (status) {
			return 0.25 * res;
		}
	}
#endif
	return 0.0;
}

int HardRock::readKey()
{
#ifdef WIN32
	if (!mConnected) {
		return 0;
	}
	int val;
	srGetCWInp(&val);
	val = ~val;
	return 0x04 | ((val&0x20)>>4) | ((val&0x02)>>1);
#else
    return 0;
#endif
}

