#include "animation.h"

//---class animation

animation::animation() {
	msElapsed = 0;
	animationTransform = NULL;
	animLength = 0;
	offset = 0;
}

animation::animation(unsigned int animLength, unsigned int offset){
	msElapsed = offset;
	this->offset = offset;
	animationTransform = NULL;
	this->animLength = animLength;
}

void animation::calcAnim(int deltaTMs) {
	debug("animation::calcAnim()");
	msElapsed += deltaTMs;
	debug(msElapsed);
	debug(animLength);

	if (animLength > 0) {
		while (msElapsed >= animLength) {
			
			msElapsed -= animLength;
			debug(msElapsed);
		}
	}

	animationTransform = animate(deltaTMs);
}

void animation::reset() {
	debug("animation::reset()");
	debug(msElapsed);
	debug(offset);
	this->msElapsed = this->offset;
	debug("animation::reset()--");
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

//--class compositeAnimation


compositeAnimation::compositeAnimation() {
	construct();
}

compositeAnimation::compositeAnimation(unsigned int offset) : animation(0, offset) {
	construct();
}

void compositeAnimation::construct() {
	lastAnim = NULL;
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

	while (t > (*times) && times != offsets->end()) {
		times++;
		anims++;
	} 

	anims--;
	provider = (*anims);

	if (provider != lastAnim) {
		lastAnim = provider;
		if (provider != NULL) {
			provider->reset();	
		}
	}

	if (provider != NULL) {	
		provider->calcAnim(deltaTMs);
		return provider->getAnimationTransform();
	} else {
		return NULL;
	}
}

//--class staticAnimation

staticAnimation::staticAnimation(transform* constTransform) {
	this->constTransform = constTransform;
}

transform* staticAnimation::animate(int deltaTMs) {
	return constTransform;
}

//--class hideObject

hideObject::hideObject() : animation() {
}

transform* hideObject::animate(int deltaTMs) {
	return new translate(0,-100,0); //hide the object below the floor plane
}