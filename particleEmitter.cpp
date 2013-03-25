#include "particleEmitter.h"

particleEmitter::particleEmitter(unsigned long numParticles, float maxSpread, float maxDist, 
								const float* particleColour, unsigned long travelTime, float particleSize,
								transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {

	float origin[] = {0,0,0};

	for (unsigned long i=0; i < numParticles; i++) {
		float target[] = {randFloat(-1*maxSpread,maxSpread),maxDist,randFloat(-1*maxSpread,maxSpread)};
		debug("new particle---");
		debug(target[0]);
		debug(target[1]);
		debug(target[2]);
		debug("---");
		animation* particleAnim = new linearTranslateAnimation(origin, target, travelTime, randFloat(0,1)*travelTime);
		add(new cube(particleSize,particleSize,particleSize,particleColour,NULL,particleAnim));
	}

}

float particleEmitter::randFloat(float low, float high) {
	float r = low + (float)rand()/((float)RAND_MAX/(high-low));
	debug("randFloat");
	debug(low);
	debug(high);
	debug(r);
	return r;
}