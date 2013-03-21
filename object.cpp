#include "object.h"

#include <GL/glut.h>

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

void object::construct(matrix* transform) {
	transformationMatrix = transform;
}

object::object() {
	construct(matrix::getIdentityMatrix());
}

object::object(matrix* transform) {
	construct(transform);
}

void object::transformAndDraw() {
	glPushMatrix();
	glLoadMatrixf(transformationMatrix->getInnerMatrix());
	draw();
	glPopMatrix();
}