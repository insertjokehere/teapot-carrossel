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
}

void cylinder::draw() {
	//based off implementation from http://www.opengl.org/discussion_boards/showthread.php/167115-Creating-cylinder
	for(int i=0; i<slices; i++) {
		float theta = ((float)i)*2.0*M_PI;
		float nextTheta = ((float)i+1)*2.0*M_PI;
		colorV(colour);
		glBegin(GL_TRIANGLE_STRIP);
			/*vertex at middle of end */ 
			glVertex3f(0.0, length, 0.0);
			/*vertices at edges of circle*/ 
			glVertex3f(radius*cos(theta), length, radius*sin(theta));
			glVertex3f (radius*cos(nextTheta), length, radius*sin(nextTheta));
			/* the same vertices at the bottom of the cylinder*/
			glVertex3f (radius*cos(nextTheta), length / 2.0, radius*sin(nextTheta));
			glVertex3f(radius*cos(theta), length / 2.0, radius*sin(theta));
			glVertex3f(0.0, length / 2.0, 0.0);
		glEnd();
	}
}