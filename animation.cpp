#include "animation.h"

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

oscillateAnimation::oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset) {
	this->targetX = targetX;
	this->targetY = targetY;
	this->targetZ = targetZ;
	this->moveTimeMs = moveTimeMs;
	this->farHoldMs = farHoldMs;
	this->nearHoldMs = nearHoldMs;
	this->offset = offset;
}

transform* oscillateAnimation::animate(int deltaTMs) {
	unsigned int realTime = getTotalMsElapsed() + offset;
	unsigned int totalAnimTime = 2 * moveTimeMs + farHoldMs + nearHoldMs;

	while (realTime > totalAnimTime) {
		realTime -= totalAnimTime;
	}

	if (realTime < moveTimeMs) {
		for (int i = 0; i<3;i++) {
			
		}
	} else if (realTime < (moveTimeMs + farHoldMs)) {

	} else if (realTime < (moveTimeMs * 2 + farHoldMs)) {

	} else {
		return NULL;
	}
}