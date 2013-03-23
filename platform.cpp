#include "platform.h"

//--platform
platform::platform(transform* constTransform, animation* animationProvider): objectgroup(constTransform,animationProvider) {
	/*objectgroup* gears = new objectgroup(NULL, NULL);
	gears->add(new gear(25, 10, NULL, new rotateAnimation(1.0, 90, rotateAnimation::AXIS_Z, 0.0)));
	gears->add(new gear(15, 5, new translate(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0), new rotateAnimation(-1.0, 25.0/15.0 * 90, rotateAnimation::AXIS_Z, 10)));
	gears->add(new gear(10, 5,  new translate(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0), new rotateAnimation(-1.0, 25.0/10.0 * 90, rotateAnimation::AXIS_Z, 0)));*/
	add(new platformBody());
}

//--platformBody
platform::platformBody::platformBody():objectgroup(NULL,NULL) {
	add(new cylinder(2.5,70.0,blue,new rotate(-90,1,0,0),NULL));
}

void platform::platformBody::initilize() {

}

void platform::platformBody::drawself() {

}

//--platformArm

platform::platformArm::platformArm(object* staticObject, transform* constTransform): objectgroup(constTransform, NULL) {

}

void platform::platformArm::drawself() {

}