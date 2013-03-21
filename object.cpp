#include "object.h"

int object::numLights = 0;
LIGHTID object::lights[] = {GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7}; //GL_LIGHT0 is reserved for global illumination

LIGHTID object::reserveLight()  {
	if (NELEMS(lights) == numLights - 1) {
		//all the lights have been reserved
		return NO_LIGHTS_AVALIBLE;
	} else {
		LIGHTID light = lights[numLights];
		numLights++;
		return light;
	}
}

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