#include "object.h"

object::object(transform* constTransform, animation* animationProvider) {
	this->constTransform = constTransform;
	this->animationProvider = animationProvider;
}

void object::animate(int deltaTMs) {
	debug("object::animate()");
	if (animationProvider != NULL) {
		animationProvider->calcAnim(deltaTMs);
	}
}

void object::transformAndDraw() {
	debug("object::transformAndDraw()");
	glPushMatrix();
	if (constTransform != NULL) {
		constTransform->apply();
	}
	if (animationProvider != NULL) {
		transform* animTransform = animationProvider->getAnimationTransform();
		if (animTransform != NULL) {
			animTransform->apply();
		}
	}
	draw();
	glPopMatrix();
}

void object::drawVertex(const float vertex[][3], unsigned int count, GLenum mode) {
	glBegin(mode);
	for (unsigned int i = 0; i < count; i++) {
		glVertex3f(vertex[i][0],vertex[i][1],vertex[i][2]);
	}
	glEnd();
}