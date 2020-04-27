#pragma once

#include <cmath>
#include "AftrGlobals.h"

namespace Aftr
{

class Wave
{
public:
	Wave(float w = 100, float a = 1, float v = 0);
	~Wave();
	static float getWaveHeight(float wavelength, float amplitude, float velocity, float phase){return sin(phase / wavelength * (float)Aftr::PI * 2.0f) * (pow(amplitude,1.0f - (phase * velocity)));}
   float getHeight(float phase);
	float getWavelength(){return wavelength;}
	float getAmplitude(){return amplitude;}
	float getVelocity(){return velocity;}
	void setWavelength(float w){wavelength = w;}
	void setAmplitude(float a){amplitude = a;}
	void setVelocity(float v){velocity = v;}
private:
	float wavelength;///wave length of the wave
	float amplitude;///amplitude of the wave
	float velocity;///dampending velocity of the wave
	//float* table;
};

}


