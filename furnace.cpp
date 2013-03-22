#include "furnace.h"

furnace::furnace(transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {
}

const float furnace::frontFace[][3] = {{-7.5,20,0}, {-7.5,0,0}, {-17.5,0,0}, {-17.5,35.0,0.0},{0.0,35.0,0.0},{0.0,20.0,0.0}};
const float furnace::sides[][3] = { {-17.5,35.0,0.0} , {-17.5,0.0,0.0}, {-17.5,35.0,45.0}, {-17.5,0.0,45.0}, {17.5,35.0,45.0}, {17.5,0.0,45.0}, {17.5,35.0,0.0} , {17.5,0.0,0.0}};
const float furnace::top[][3] = { {-17.5,35.0,0.0},{-17.5,35.0,45.0},{17.5,35.0,45.0},{17.5,35.0,0.0} };

void furnace::drawSelf() {
	debug("furnace::draw()");

	colorV(blue);

	//front
	//The front face is a concave polygon, so it has to be drawn in two halves
	object::drawVertex(frontFace,6,GL_POLYGON);
	glPushMatrix();
		glRotatef(180,0,1,0);
		object::drawVertex(frontFace,6,GL_POLYGON);
	glPopMatrix();
	//sides
	colorV(red);
	object::drawVertex(sides,8,GL_QUAD_STRIP);

	object::drawVertex(top, 4, GL_POLYGON);

	float spot_pos[] = {0.,0.,0.,1.};
	float spot_look[] = {0.,10.,0.,1.};

	glLightfv(light, GL_POSITION, spot_pos);
	glLightfv(light, GL_SPOT_DIRECTION, spot_look);
}

void furnace::initilize() {
	light = reserveLight();
	configSpotLight(light, orange, orange, orange, 30.0,0.01);

	add(new cube(20,8,0.5,green, new translate(0,0,-1),NULL)); //left door
	add(new cube(20,8,0.5,green, new translate(-8,0,-1),NULL)); //right door
}
