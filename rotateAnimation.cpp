#include "rotateAnimation.h"

rotateAnimation::rotateAnimation(int direction, float speedDPS, unsigned short axis, float rotateOffset) : animation() {
	debug("rotateAnimation::rotateAnimation()");
	this->direction = direction;
	this->speedDPS = speedDPS;

	this->x = ((axis & AXIS_X) == AXIS_X) ? 1 : 0;
	this->y = ((axis & AXIS_Y) == AXIS_Y) ? 1 : 0;
	this->z = ((axis & AXIS_Z) == AXIS_Z) ? 1 : 0;

	this->rotateOffset = rotateOffset;
}

transform* rotateAnimation::animate(int deltaTMs) {
	debug("rotateAnimation::animate()");
	float theta = ((this->speedDPS * (getTotalMsElapsed() / 1000.0)) * direction)+rotateOffset;
	return new rotate(theta, x, y, z);
}