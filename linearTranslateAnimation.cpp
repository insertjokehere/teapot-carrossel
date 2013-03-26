#include "linearTranslateAnimation.h"

linearTranslateAnimation::linearTranslateAnimation(float source[3], float target[3], unsigned int moveTimeMs, unsigned int offset) : animation(moveTimeMs, offset) {
	debug("linearTranslateAnimation::linearTranslateAnimation()");
	for (int i=0; i < 3; i++) {
		this->source[i] = source[i];
		this->target[i] = target[i];
	}
}

transform* linearTranslateAnimation::animate(int deltaTMs) {
	//debug("linearTranslateAnimation::animate()");

	float t = (float)getTotalMsElapsed() / (float)getAnimLength();
	float position[3];

	//debug(getTotalMsElapsed());
	//debug(getAnimLength());
	//debug(t);

	for (int i = 0; i<3; i++) {
		debug(source[i]);
		debug(target[i]);
		position[i] = interpolate(source[i], target[i], t);
		debug(position[i]);
	}

	return new translate(position);

}

float linearTranslateAnimation::interpolate(float from, float to, float t) {
	float i = from + ((to - from) * t);
	/*debug("linearTranslateAnimation::interpolate()");
	debug(from);
	debug(to);
	debug(t);
	debug(i);*/
	return i;
}