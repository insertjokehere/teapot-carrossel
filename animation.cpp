#include "animation.h"

animation::animation() {
	msElapsed = 0;
	animationTransform = NULL;
}

void animation::calcAnim(int deltaTMs) {
	msElapsed += deltaTMs;
	animationTransform = this->animate(deltaTMs);
}

transform* animation::getAnimationTransform() {
	return animationTransform;
}

rotateAnimation::rotateAnimation(int direction, float speedDPS, unsigned short axis, float rotateOffset) : animation() {
	this->direction = direction;
	this->speedDPS = speedDPS;

	this->x = ((axis & AXIS_X) == AXIS_X) ? 1 : 0;
	this->y = ((axis & AXIS_Y) == AXIS_Y) ? 1 : 0;
	this->z = ((axis & AXIS_Z) == AXIS_Z) ? 1 : 0;

	lastTheta = rotateOffset;
}

transform* rotateAnimation::animate(int deltaTMs) {
	lastTheta += (this->speedDPS * (deltaTMs / 1000.0)) * direction;
	while (lastTheta > 360) {
		lastTheta -= 360;
	}
	while (lastTheta < 0) {
		lastTheta += 360;
	}
	return new rotate(lastTheta, x, y, z);
}