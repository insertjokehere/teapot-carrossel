#include "platform.h"

//--platform
platform::platform(transform* constTransform, animation* animationProvider): objectgroup(constTransform,animationProvider) {
	/*objectgroup* gears = new objectgroup(NULL, NULL);
	gears->add(new gear(25, 10, NULL, new rotateAnimation(1.0, 90, rotateAnimation::AXIS_Z, 0.0)));
	gears->add(new gear(15, 5, new translate(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0), new rotateAnimation(-1.0, 25.0/15.0 * 90, rotateAnimation::AXIS_Z, 10)));
	gears->add(new gear(10, 5,  new translate(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0), new rotateAnimation(-1.0, 25.0/10.0 * 90, rotateAnimation::AXIS_Z, 0)));*/
	add(new platformBody(NULL,new rotateAnimation(1.0,90,rotateAnimation::AXIS_Y, 0.0)));

	compositeTransform* gear1Transform = new compositeTransform();
	gear1Transform->add(new translate(gear::getRadius(15)+gear::getRadius(25)+gear::SPACING,0,0));
	gear1Transform->add(new rotate(-90,1,0,0));
	add(new gear(15,4,gear1Transform, NULL));

	compositeTransform* gear2Transform = new compositeTransform();
	gear2Transform->add(new translate(gear::getRadius(10) + 2*gear::getRadius(15)+gear::getRadius(25)+2*gear::SPACING,0,0));
	gear2Transform->add(new rotate(-90,1,0,0));
	add(new gear(10,4,gear2Transform, NULL));	
}

//--platformBody
platform::platformBody::platformBody(transform* constTransform, animation* animationProvider): objectgroup(constTransform,animationProvider) {
	add(new cylinder(2.5,70.0,blue,new rotate(-90,1,0,0),NULL)); //center shaft

	add(new gear(25,4,new rotate(-90,1,0,0),NULL));
	
	compositeTransform* coneTransform = new compositeTransform();
	coneTransform->add(new translate(0,70.0,-3));
	coneTransform->add(new rotate(-45,1,0,0));
	coneTransform->add(new translate(0,0,4.5 * -0.5));
	add(new cone(3,4.5,red,coneTransform,NULL));

	add(new platformArm(NULL, NULL));
}

void platform::platformBody::initilize() {

}

void platform::platformBody::drawself() {

}

//--platformArm

platform::platformArm::platformArm(object* staticObject, transform* constTransform): objectgroup(constTransform, NULL) {
	add(new cube(3,3,25,grey,new translate(-1.5,32,0),NULL));
	add(new cube(10,2,10,grey,new translate(-5,35,20),NULL));
}

void platform::platformArm::drawself() {

}