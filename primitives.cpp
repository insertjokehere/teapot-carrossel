#include "primitives.h"

cube::cube(float width, float height, float depth, const float* colour, transform* constTransform, animation* animationProvider) : object(constTransform,animationProvider) {
	this->height = height;
	this->width = width;
	this->depth = depth;
	this->colour = colour;
}

void cube::draw() {
	debug("cube::draw()");

	float body[][3]  = { {0,0,0},{0,height,0}, {0,0,depth},{0,height,depth}, {width,0,depth},{width,height,depth},{width,0,0},{width,height,0},{0,0,0},{0,height,0}};
	float top[][3] = { {0,height,0},{0,height,depth},{width,height,depth},{width,height,0} };
	float bottom[][3] = { {0,0,0},{0,0,depth},{width,0,depth},{width,0,0} };

	colorV(colour);
	object::drawVertex(body, 10, GL_QUAD_STRIP);
	object::drawVertex(top,4,GL_POLYGON);
	object::drawVertex(bottom,4,GL_POLYGON);
}

cylinder::cylinder(float radius, float length, const float* colour, transform* constTransform, animation* animationProvider):object(constTransform, animationProvider) {
	this->radius = radius;
	this->length = length;
	this->colour = colour;
}

void cylinder::draw() {
	colorV(colour);
	GLUquadric *q = gluNewQuadric();
	gluCylinder(q, radius, radius, length, slices, slices);
	gluQuadricDrawStyle(q, GLU_LINE);
}