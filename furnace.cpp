#include "furnace.h"

furnace::furnace(transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {
	add(new furnaceTop(new translate(0.0,35.0,0.0), NULL));
	add(new cube(35.0,35.0,45.0,red, new translate(-17.5,0,0), NULL));
}

furnace::furnaceTop::furnaceTop(transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {
	float leftDoorAnimTarget[3] = {7.0,0.0,0.0};
	add(new cube(8,20,0.5,green, new translate(0,0,-0.5), new oscillateAnimation(leftDoorAnimTarget, 2000,2000,0,0))); //left door
	float rightDoorAnimTarget[3] = {-7.0,0.0,0.0};
	add(new cube(8,20,0.5,orange, new translate(-8,0,-0.5),new oscillateAnimation(rightDoorAnimTarget, 2000,2000,0,0))); //right door
	add(new cube(18,2,1.5, red, new translate(-9,20,-1.5), NULL)); //top guidebar

	compositeTransform* chimneyTransform = new compositeTransform();
	chimneyTransform->add(new translate(0,35,12));
	chimneyTransform->add(new rotate(-90,AXIS_X));
	add(new cylinder(4,12,false,white,chimneyTransform,NULL));
	add(new particleEmitter(2000,5,40,grey,5000,0.25,new translate(0,47,12),NULL));

	compositeTransform* lampTransform = new compositeTransform();
	lampTransform->add(new translate(17.5,35,12));
	lampTransform->add(new rotate(-90,AXIS_Y));
	lampTransform->add(new rotate(-60,AXIS_X));
	add(new spotlamp(white,white,white,white,15,4,lampTransform,NULL));

}

const float furnace::furnaceTop::frontFace[][3] = {{-7.5,20,0}, {-7.5,0,0}, {-17.5,0,0}, {-17.5,35.0,0.0},{0.0,35.0,0.0},{0.0,20.0,0.0}};
const float furnace::furnaceTop::sides[][3] = { {-17.5,35.0,0.0} , {-17.5,0.0,0.0}, {-17.5,35.0,45.0}, {-17.5,0.0,45.0}, {17.5,35.0,45.0}, {17.5,0.0,45.0}, {17.5,35.0,0.0} , {17.5,0.0,0.0}};
const float furnace::furnaceTop::top[][3] = { {-17.5,35.0,0.0},{-17.5,35.0,45.0},{17.5,35.0,45.0},{17.5,35.0,0.0} };

void furnace::furnaceTop::drawSelf() {
	debug("furnaceTop::draw()");

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

