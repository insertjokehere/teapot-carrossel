#include "animation.h"

//---class animation

animation::animation() {
	msElapsed = 0ul;
	animationTransform = NULL;
	animLength = 0ul;
	offset = 0ul;
}

animation::animation(unsigned long animLength, unsigned long offset){
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

//--class animationSequence


animationSequence::animationSequence() : animation() {
	construct();
}

animationSequence::animationSequence(unsigned int offset) : animation(0, offset) {
	construct();
}

void animationSequence::construct() {
	lastAnim = NULL;
	this->offsets = new std::list<unsigned int>();
	this->animations = new std::list<animation*>();
}

void animationSequence::add(animation* animationProvider, unsigned int lengthMs) {
	offsets->insert(offsets->end(), getAnimLength());
	animations->insert(animations->end(), animationProvider);

	setAnimLength(getAnimLength() + lengthMs);
}

transform* animationSequence::animate(int deltaTMs) {
	debug("animationSequence::animate()");

	std::list<unsigned int>::iterator times = offsets->begin();
	std::list<animation*>::iterator anims = animations->begin();

	animation* provider = NULL;

	unsigned int t = getTotalMsElapsed();

	while (t > (*times) && times != offsets->end()) {
		provider = (*anims);
		times++;
		anims++;
	} 

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

staticAnimation::staticAnimation(transform* constTransform): animation() {
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