#include "spotlamp.h"

spotlamp::spotlamp(const float* colour, const float* ambient, const float* diffuse, const float* specular, float spot_cutoff, float spot_exponent, transform* constTransform, animation* animationProvider): object(constTransform, animationProvider) {
	this->colour = colour;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->spot_cutoff = spot_cutoff;
	this->spot_exponent = spot_exponent;
}

void spotlamp::draw() {
	float light_pos[] = {0.0,0.0,0.0,1.0};
	float light_dir[] = {0,0,1.0,1.0};

	glLightfv(light,GL_POSITION,light_pos);
	glLightfv(light,GL_SPOT_DIRECTION,light_dir);

	colorV(colour);
	GLUquadric *q = gluNewQuadric();
	gluCylinder(q, 0, 3, 5, 20, 20);
	gluQuadricDrawStyle(q, GLU_FILL);
}

void spotlamp::initilize() {
	light = reserveLight();
	configSpotLight(light, ambient, diffuse, specular, spot_exponent, spot_cutoff);
}