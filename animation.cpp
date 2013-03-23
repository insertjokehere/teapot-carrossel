#include "animation.h"

//---class animation

animation::animation() {
	msElapsed = 0;
	animationTransform = NULL;
	animLength = 0;
}

animation::animation(unsigned int animLength, unsigned int offset){
	msElapsed = offset;
	animationTransform = NULL;
	this->animLength = animLength;
}

void animation::calcAnim(int deltaTMs) {
	debug("animation::calcAnim()");
	msElapsed += deltaTMs;

	if (animLength > 0) {
		while (msElapsed >= animLength) {
			debug(msElapsed);
			debug(animLength);
			msElapsed -= animLength;
		}
	}

	animationTransform = animate(deltaTMs);
}

transform* animation::getAnimationTransform() {
	return animationTransform;
}

unsigned long animation::getTotalMsElapsed() {
	return msElapsed;
}

void animation::setAnimLength(unsigned int animLength) {
	this->animLength = animLength;
}

unsigned int animation::getAnimLength() {
	return animLength;
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
	construct();
}

compositeAnimation::compositeAnimation(unsigned int offset) : animation(0, offset) {
	construct();
}

void compositeAnimation::construct() {
	this->offsets = new std::list<unsigned int>();
	this->animations = new std::list<animation*>();
}

void compositeAnimation::add(animation* animationProvider, unsigned int lengthMs) {
	offsets->insert(offsets->end(), getAnimLength());
	animations->insert(animations->end(), animationProvider);

	setAnimLength(getAnimLength() + lengthMs);
}

transform* compositeAnimation::animate(int deltaTMs) {
	debug("compositeAnimation::animate()");
	std::list<unsigned int>::iterator times = offsets->begin();
	std::list<animation*>::iterator anims = animations->begin();

	animation* provider = NULL;

	unsigned int t = getTotalMsElapsed();
	
	while (t >= (*times)) {
		debug("t");
		debug(t);
		debug("*times");
		debug((*times));
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

//--class staticAnimation

staticAnimation::staticAnimation(transform* constTransform) {
	this->constTransform = constTransform;
}

transform* staticAnimation::animate(int deltaTMs) {
	return constTransform;
}

//--class oscillateAnimation

oscillateAnimation::oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset): compositeAnimation(offset) {
	// |---moveTimeMs-------------|---farHoldMs-----|---moveTimeMs-------------|---nearHoldMs----|
	// | linearTranslateAnimation | staticAnimation | linearTranslateAnimation | staticAnimation |

	float origin[3] = {0,0,0};

	add(new linearTranslateAnimation(origin, target, moveTimeMs, 0), moveTimeMs);
	add(new staticAnimation(new translate(target)),farHoldMs);
	add(new linearTranslateAnimation(target, origin, moveTimeMs, 0), moveTimeMs);
	add(new staticAnimation(NULL), nearHoldMs);
}