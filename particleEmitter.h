#ifndef H_PARTICLEEMITTER
#define H_PARTICLEEMITTER

#include "objectgroup.h"
#include "linearTranslateAnimation.h"
#include "primitives.h"

class particleEmitter : public objectgroup {
private:
	float randFloat(float low, float high);
public:
	particleEmitter(unsigned long numParticles, float maxSpread, float maxDist, 
					const float* particleColour, unsigned long travelTime, float particleSize,
					transform* constTransform, animation* animationProvider);
};

#endif