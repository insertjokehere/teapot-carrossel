#include "linearTranslateAnimation.h"

linearTranslateAnimation::linearTranslateAnimation(float source[3], float target[3], unsigned int moveTimeMs, unsigned int offset) : animation(moveTimeMs, offset) {
	this->source = source;
	this->target = target;
}

transform* linearTranslateAnimation::animate(int deltaTMs) {
	debug("linearTranslateAnimation::animate()");

	float t = (float)getTotalMsElapsed() / (float)getAnimLength();
	float position[3];

	debug(t);

	for (int i = 0; i<3; i++) {
		position[i] = interpolate(source[i], target[i], t);
		debug(position[i]);
	}

	return new translate(position);

}

float linearTranslateAnimation::interpolate(float from, float to, float t) {
	return from + ((to - from) * t);
}