#include "animation.h"

//---class animation

animation::animation() {
	msElapsed = 0;
	animationTransform = NULL;
}

void animation::calcAnim(int deltaTMs) {
	debug("animation::calcAnim()");
	msElapsed += deltaTMs;
	animationTransform = animate(deltaTMs);
}

transform* animation::getAnimationTransform() {
	return animationTransform;
}

unsigned long animation::getTotalMsElapsed() {
	return msElapsed;
}

//--class rotateAnimation

rotateAnimation::rotateAnimation(int direction, float speedDPS, unsigned short axis, float rotateOffset) : animation() {
	debug("rotateAnimation::rotateAnimation()");
	this->direction = direction;
	this->speedDPS = speedDPS;

	this->x = ((axis & AXIS_X) == AXIS_X) ? 1 : 0;
	this->y = ((axis & AXIS_Y) == AXIS_Y) ? 1 : 0;
	this->z = ((axis & AXIS_Z) == AXIS_Z) ? 1 : 0;

	lastTheta = rotateOffset;
}

transform* rotateAnimation::animate(int deltaTMs) {
	debug("rotateAnimation::animate()");
	float step = (this->speedDPS * (deltaTMs / 1000.0)) * direction;
	lastTheta += step;
	debug(step);
	debug(lastTheta);
	while (lastTheta > 360) {
		lastTheta -= 360;
	}
	while (lastTheta < 0) {
		lastTheta += 360;
	}
	return new rotate(lastTheta, x, y, z);
}

//--class compositeAnimation


compositeAnimation::compositeAnimation() {
	construct(0);
}

compositeAnimation::compositeAnimation(unsigned int offset) {
	construct(offset);
}

void compositeAnimation::construct(unsigned int offset) {
	this->offset = offset;
	this->totalTime = 0;

	this->offsets = new std::list<unsigned int>();
	this->animations = new std::list<animation*>();
}

void compositeAnimation::add(animation* animationProvider, unsigned int lengthMs) {
	offsets->insert(offsets->end(), totalTime);
	animations->insert(animations->end(), animationProvider);
	totalTime += lengthMs;
}

transform* compositeAnimation::animate(int deltaTMs) {
	std::list<unsigned int>::iterator times = offsets->begin();
	std::list<animation*>::iterator anims = animations->begin();

	animation* provider = NULL;

	unsigned int adjustedTime = getTotalMsElapsed() + offset;
	
	while (adjustedTime > totalTime) {
		adjustedTime -= totalTime;
	}

	while (adjustedTime > (*times)) {
		provider = (*anims);
		times++;
		anims++;
	}

	if (provider != NULL) {
		return provider->animate(deltaTMs);
	} else {
		return NULL;
	}
}

//--class linearTranslateAnimation

//--class staticAnimation

staticAnimation::staticAnimation(transform* constTransform) {
	this->constTransform = constTransform;
}

staticAnimation::transform* animate(int deltaTMs) {
	return constTransform;
}

//--class oscillateAnimation

oscillateAnimation::oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset) {
	// |---moveTimeMs--------------|---farHoldMs------|---moveTimeMs--------------|---nearHoldMs----|
	// | linearTranslateAnimation  | staticAnimation  | linearTranslateAnimation  | staticAnimation |
}