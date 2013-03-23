#include "furnace.h"

furnace::furnace(transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {
	float leftDoorAnimTarget[3] = {-7.0,0.0,0.0};
	add(new cube(8,20,0.5,green, new translate(0,0,-0.5), new oscillateAnimation(leftDoorAnimTarget, 2000,3000,3000,0))); //left door
	float rightDoorAnimTarget[3] = {15.0,0.0,0.0};
	add(new cube(8,20,0.5,green, new translate(-8,0,-0.5),new oscillateAnimation(rightDoorAnimTarget, 2000,3000,3000,0))); //right door
	add(new cube(18,2,1.5, red, new translate(-9,20,-1.5), NULL)); //top guidebar
}

const float furnace::frontFace[][3] = {{-7.5,20,0}, {-7.5,0,0}, {-17.5,0,0}, {-17.5,35.0,0.0},{0.0,35.0,0.0},{0.0,20.0,0.0}};
const float furnace::sides[][3] = { {-17.5,35.0,0.0} , {-17.5,0.0,0.0}, {-17.5,35.0,45.0}, {-17.5,0.0,45.0}, {17.5,35.0,45.0}, {17.5,0.0,45.0}, {17.5,35.0,0.0} , {17.5,0.0,0.0}};
const float furnace::top[][3] = { {-17.5,35.0,0.0},{-17.5,35.0,45.0},{17.5,35.0,45.0},{17.5,35.0,0.0} };

void furnace::drawSelf() {
	debug("furnace::draw()");

	float spot_pos[] = {0.,10.,-20.,1.};
	float spot_look[] = {0.,1.,0.,1.};

	glLightfv(light, GL_POSITION, spot_pos);
	glLightfv(light, GL_SPOT_DIRECTION, spot_look);

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

	
}

void furnace::initilize() {
	light = reserveLight();
	configSpotLight(light, orange, orange, orange, 30.0,0.01);	
}
