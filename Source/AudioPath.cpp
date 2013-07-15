/*
  ==============================================================================

    AudioPath.cpp
    Created: 10 May 2013 8:33:59pm
    Author:  Frank A. Stevenson

  ==============================================================================
*/

#include "AudioPath.h"
#include "CwGen.h"
#include "Receiver.h"
#include "Waterfall.h"

static CwGen     *gCW_keyer;
#define CIRCULAR_BUFFER_SIZE 10000

static float gIbuffer[CIRCULAR_BUFFER_SIZE];
static float gQbuffer[CIRCULAR_BUFFER_SIZE];
volatile int gReadPos = 0;
volatile int gWritePos = 0;

static float gAFbuffer[CIRCULAR_BUFFER_SIZE];
volatile int gReadPosAF = 0;
volatile int gWritePosAF = CIRCULAR_BUFFER_SIZE/4;

bool gSwapChannels = false;
double gCWpitch1 = 0.08f;

/**
 *
 *  IF audio devices (quadrature)
 *
 */

class SoftRockCallbackIF : public AudioIODeviceCallback
{
public:
	SoftRockCallbackIF();
    virtual ~SoftRockCallbackIF();

    virtual void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples);

	virtual void audioDeviceAboutToStart (AudioIODevice* device);

    virtual void audioDeviceStopped();

    virtual void audioDeviceError (const String& errorMessage);
private:
	double mPos;
};

SoftRockCallbackIF::SoftRockCallbackIF() :
	mPos(0.0)		
{

}

SoftRockCallbackIF::~SoftRockCallbackIF()
{
}


void SoftRockCallbackIF::audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples)
{
#if 0
	float val = 0.0;
	for (int i=0;i<numSamples;i++) {
		val = (float)sin(mPos);
		mPos += 0.04f;
		while (mPos > 6.28318530718f) {
			mPos -= 6.28318530718f;
		}
		for (int j=0; j<numOutputChannels; j++) {
			outputChannelData[j][i] = 0.5f * val;
		}
	}
#else

	int newpos = gWritePos + numSamples;
	size_t size1 = numSamples;
	size_t size2 = 0;
	if (newpos>CIRCULAR_BUFFER_SIZE) {
		size1 = CIRCULAR_BUFFER_SIZE - gWritePos;
		newpos = newpos - CIRCULAR_BUFFER_SIZE;
		size2 = newpos > CIRCULAR_BUFFER_SIZE ? CIRCULAR_BUFFER_SIZE : newpos;
		newpos = size2;
	}
	if (numInputChannels>0) {
		memcpy(&gIbuffer[gWritePos],inputChannelData[gSwapChannels?1:0],size1*sizeof(float));
		if (size2) {
			memcpy(gIbuffer,&inputChannelData[gSwapChannels?1:0][size1],size2*sizeof(float));
		}
	}
	if (numInputChannels>1) {
		memcpy(&gQbuffer[gWritePos],inputChannelData[gSwapChannels?0:1],size1*sizeof(float));
		if (size2) {
			memcpy(gQbuffer,&inputChannelData[gSwapChannels?0:1][size1],size2*sizeof(float));
		}
	}
	gWritePos = newpos;
#endif
}

void SoftRockCallbackIF::audioDeviceAboutToStart (AudioIODevice* device)
{
}

void SoftRockCallbackIF::audioDeviceStopped()
{
}

void SoftRockCallbackIF::audioDeviceError (const String& errorMessage)
{
}




/**
 *
 *  AF audio devices real / mono (stereo duplicate)
 *
 */

class SoftRockCallbackAF : public AudioIODeviceCallback
{
public:
	SoftRockCallbackAF();
    virtual ~SoftRockCallbackAF();

    virtual void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples);

	virtual void audioDeviceAboutToStart (AudioIODevice* device);

    virtual void audioDeviceStopped();

    virtual void audioDeviceError (const String& errorMessage);
private:
	double mPos;
};

SoftRockCallbackAF::SoftRockCallbackAF() :
	mPos(0.0)		
{

}

SoftRockCallbackAF::~SoftRockCallbackAF()
{
}


void SoftRockCallbackAF::audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples)
{
	float val = 0.0;
	for (int i=0;i<numSamples;i++) {
		val = (float)sin(mPos) * gCW_keyer->getEnvelopeSample() + gAFbuffer[gReadPosAF++];
		if (gReadPosAF>=CIRCULAR_BUFFER_SIZE) {
			gReadPosAF = 0;
		}
		mPos += gCWpitch1;
		while (mPos > 6.28318530718) {
			mPos -= 6.28318530718;
		}
		for (int j=0; j<numOutputChannels; j++) {
			outputChannelData[j][i] = 0.5f * val;
		}
	}
}

void SoftRockCallbackAF::audioDeviceAboutToStart (AudioIODevice* device)
{
}

void SoftRockCallbackAF::audioDeviceStopped()
{
}

void SoftRockCallbackAF::audioDeviceError (const String& errorMessage)
{
}





class AudioPath {
public:
	AudioPath(AudioIODeviceCallback *cb);
	~AudioPath();

	AudioDeviceSelectorComponent* mSelector;  // The tabbed UI component has ownership
	void getAudioDeviceSetup(AudioDeviceManager::AudioDeviceSetup &setup);

private:
	ScopedPointer<AudioDeviceManager> mDevManager;
	AudioIODeviceCallback *mCallback;
};



AudioPath::AudioPath(AudioIODeviceCallback *cb) :
	mCallback(cb)
{
	mDevManager = new AudioDeviceManager();
	mDevManager->initialise(2,2,NULL,true);
	mSelector = new AudioDeviceSelectorComponent(*mDevManager,0,2,2,2,false,false,true,true);
	mDevManager->addAudioCallback(static_cast<juce::AudioIODeviceCallback*>(mCallback));
}

AudioPath::~AudioPath()
{
	// Save configuration
	XmlElement *state =  mDevManager->createStateXml();
	// String stateData = state->createDocument("SoftRockCw");
	delete state;
	mDevManager->closeAudioDevice();
	mDevManager = 0;
	// mSelector = 0;
	delete mCallback;
}

void AudioPath::getAudioDeviceSetup(AudioDeviceManager::AudioDeviceSetup &setup)
{
	mDevManager->getAudioDeviceSetup(setup);
}


static AudioPath *gAP_IF;
static AudioPath *gAP_AF;
static Receiver  *gRecv;
static Waterfall *gWaterfall;

void initAudio()
{
	memset(gIbuffer,0,sizeof(gIbuffer));
	memset(gQbuffer,0,sizeof(gQbuffer));
	memset(gAFbuffer,0,sizeof(gAFbuffer));
	gAP_IF = new AudioPath(new SoftRockCallbackIF());
	gAP_AF = new AudioPath(new SoftRockCallbackAF());
	gCW_keyer = new CwGen();
	gRecv = new Receiver();
	gWaterfall = new Waterfall();
}

void deinitAudio()
{
	delete gAP_IF;
	delete gAP_AF;
	delete gCW_keyer;
	delete gRecv;
	delete gWaterfall;
}

Receiver* getReceiver(int num)
{
	if (num==0) {
		return gRecv;
	}
	return NULL;
}



AudioDeviceSelectorComponent* getAudioSelector(int num)
{
	if (num==0) {
		return gAP_IF->mSelector;
	}
	return gAP_AF->mSelector;
}

float CoreTimer::mTuneOffset = 0.0;
bool CoreTimer::mRetune = false;
int CoreTimer::mBandChange = 0;

CoreTimer::CoreTimer(HardRock *radio, RadioPanel *panel) :
	mRadio(radio),
	mPanel(panel),
	mNumTicks(0),
	mTuneStart(0.0)
{
}

CoreTimer::~CoreTimer()
{
}

CoreTimer::modulation CoreTimer::mCurrentMod = CoreTimer::eUSB;
float CoreTimer::mCWfreq = 500;

void CoreTimer::setModulation(modulation mod)
{
	mCurrentMod = mod;
}

void CoreTimer::setChannelSwap(bool swap)
{
	gSwapChannels = swap;
}

void CoreTimer::tuneReciever(int num, float freq)
{
	if (num==0) {
		AudioDeviceManager::AudioDeviceSetup setup;
		gAP_IF->getAudioDeviceSetup(setup);
		float samplerate = setup.sampleRate;
		freq = 0.5f * freq * samplerate;
		switch (mCurrentMod) {
		case eLSB:
			gRecv->setWindow(freq, freq - 3000.0, 0.0); // LSB
			break;
		case eCW:
			{
				double hw = 300.0;
				gRecv->setWindow(freq - hw, freq + hw, mCWfreq-hw); // CW
			}
			break;
		default:
		case eUSB:
			gRecv->setWindow(freq, freq + 3000.0, 0.0); // USB
			break;
		}
	}
}

#define NUM_BANDS 9
static double bands[NUM_BANDS] =     { 1.8 , 3.6, 7.1, 10.1, 14.2, 18.1, 21.3, 24.95, 28.5 };
static double bands_mem[NUM_BANDS] = { 1.8 , 3.6, 7.1, 10.1, 14.2, 18.1, 21.3, 24.95, 28.5 };

void CoreTimer::hiResTimerCallback()
{
	// Handle band change
	if (mBandChange) {
		double err = 100.0;
		double freq = mRadio->getLO();
		int best = 0;
		for (int i=0; i< NUM_BANDS; i++) {
			double e = abs(freq - bands[i]);
			if (e<err) {
				err = e;
				best = i;
			}
		}
		int new_band = best + mBandChange;
		if ((new_band>=0) && (new_band<NUM_BANDS)) {
			bands_mem[best] = freq;
			mRadio->setLO(bands_mem[new_band]);
		}
		mBandChange = 0;
		mNumTicks = 0;
	}

	// Tune LO
	if (mTuneOffset) {
		if (mTuneStart==0.0) {
			mTuneStart = mRadio->getLO();
		}
		mRadio->setLO(mTuneStart + 0.000001 * mTuneOffset*gRecv->getRateIn());
		mNumTicks = 0;
	}
	if (mRetune) {
		mTuneOffset = 0.0f;
		mTuneStart = 0.0;
		mRetune = false;
		mNumTicks = 0;
	}

	// Update sample rates at regular intervals
	if ((mNumTicks&0x1ff)==0) {
		AudioDeviceManager::AudioDeviceSetup setup;
		gAP_IF->getAudioDeviceSetup(setup);
		gRecv->setInputSamplerate((int)setup.sampleRate);
		mRadio->setWidth((int)setup.sampleRate);
		gAP_AF->getAudioDeviceSetup(setup);
		gRecv->setOutputSamplerate((int)setup.sampleRate);
		mPanel->setLoFreq( mRadio->getLO() );
		mPanel->setTuneFreq( mRadio->getLO() + gRecv->getTuned() );
		gCWpitch1 = (double)mCWfreq*6.28318530718/setup.sampleRate;
	}
	mNumTicks++;

	// Update keyer / paddle state
	int key = mRadio->readKey();
	if (key&0x04) {
		gCW_keyer->setPaddleState(key&0x03);
	}


	// Transfer data to reciever
	int rp = gReadPos;
	int wp = gWritePos;
	if (wp>rp) {
		int num = wp-rp;
		gRecv->pushSamples(&gIbuffer[rp],&gQbuffer[rp],num);
		gWaterfall->pushSamples(&gIbuffer[rp],&gQbuffer[rp],num);
	} else if (wp<rp) {
		int num = CIRCULAR_BUFFER_SIZE - rp;
		gRecv->pushSamples(&gIbuffer[rp],&gQbuffer[rp],num);
		gWaterfall->pushSamples(&gIbuffer[rp],&gQbuffer[rp],num);
		gRecv->pushSamples(gIbuffer,gQbuffer,wp);
		gWaterfall->pushSamples(gIbuffer,gQbuffer,wp);
	}
	gReadPos = wp;

	int numOut = gRecv->getNumReadySamples();
	int newpos = gWritePosAF + numOut;
	size_t size1 = numOut;
	size_t size2 = 0;
	if (newpos>CIRCULAR_BUFFER_SIZE) {
		size1 = CIRCULAR_BUFFER_SIZE - gWritePosAF;
		newpos = newpos - CIRCULAR_BUFFER_SIZE;
		size2 = newpos > CIRCULAR_BUFFER_SIZE ? CIRCULAR_BUFFER_SIZE : newpos;
		newpos = size2;
	}
	if (size1) {
		gRecv->getSamples(&gAFbuffer[gWritePosAF],size1);
	}
	if (size2) {
		gRecv->getSamples(gAFbuffer,size2);
	}

	gWritePosAF = newpos;
}


