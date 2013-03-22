#include "furnace.h"

furnace::furnace(transform* constTransform, animation* animationProvider) : object(constTransform, animationProvider) {

}

const float furnace::frontFace[][3] = {{-7.5,20,0}, {-7.5,0,0}, {-17.5,0,0}, {-17.5,35.0,0.0},{17.5,35.0,0.0},{17.5,0.0,0.0},{7.5,0.0,0.0},{7.5,20.0,0.0}};
const float furnace::side1[][3] = { {-17.5,35.0,0.0} , {-17.5,35.0,45.0}, {-17.5,0.0,45.0}, {-17.5,0.0,0.0}};
const float furnace::side2[][3] = { {17.5,35.0,0.0} , {17.5,35.0,45.0}, {17.5,0.0,45.0}, {17.5,0.0,0.0}};

void furnace::draw() {
	debug("furnace::draw()");

	colorV(blue);

	//front
	object::drawVertex(frontFace,8,GL_POLYGON);
	//sides
	object::drawVertex(side1,4,GL_POLYGON);
	object::drawVertex(side2,4,GL_POLYGON);

	float spot_pos[] = {0.,0.,0.,1.};
	float spot_look[] = {0.,10.,0.,1.};

	glLightfv(light, GL_POSITION, spot_pos);
	glLightfv(light, GL_SPOT_DIRECTION, spot_look);
}

void furnace::initilize() {
	light = reserveLight();
	configSpotLight(light, orange, orange, orange, 30.0,0.01);
}
