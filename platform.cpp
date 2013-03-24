#include "platform.h"

//--platform
platform::platform(transform* constTransform, animation* animationProvider): objectgroup(constTransform,animationProvider) {
	/*objectgroup* gears = new objectgroup(NULL, NULL);
	gears->add(new gear(25, 10, NULL, new rotateAnimation(1.0, 90, rotateAnimation::AXIS_Z, 0.0)));
	gears->add(new gear(15, 5, new translate(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0), new rotateAnimation(-1.0, 25.0/15.0 * 90, rotateAnimation::AXIS_Z, 10)));
	gears->add(new gear(10, 5,  new translate(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0), new rotateAnimation(-1.0, 25.0/10.0 * 90, rotateAnimation::AXIS_Z, 0)));*/


	compositeAnimation* anims[3] = {new compositeAnimation(),new compositeAnimation(),new compositeAnimation()};
	int direction[] = {1,-1,1};
	float gearRatio[] = {1, 25.0/15.0, 25.0/10.0};
	unsigned short axis[] = {AXIS_Y,AXIS_Z,AXIS_Z};

	for (int i = 0; i<4; i++) {
		for (int j = 0; j < 3; j++) {
			anims[j]->add(new staticAnimation(new rotate(90*i,axis[j])),4000);
			anims[j]->add(new rotateAnimation(direction[j],45*gearRatio[j],axis[j], 90*i),2000);
		}
	}

	add(new platformBody(NULL,anims[0]));

	compositeTransform* gear1Transform = new compositeTransform();
	gear1Transform->add(new translate(gear::getRadius(15)+gear::getRadius(25)+gear::SPACING,0,0));
	gear1Transform->add(new rotate(-90,1,0,0));
	add(new gear(15,4,gear1Transform, anims[1]));

	compositeTransform* gear2Transform = new compositeTransform();
	gear2Transform->add(new translate(gear::getRadius(10) + 2*gear::getRadius(15)+gear::getRadius(25)+2*gear::SPACING,0,0));
	gear2Transform->add(new rotate(-90,1,0,0));
	add(new gear(10,4,gear2Transform, anims[2]));	
}

//--platformBody
platform::platformBody::platformBody(transform* constTransform, animation* animationProvider): objectgroup(constTransform,animationProvider) {
	const float* lampColours[]={red, blue, green, orange};

	for (int i = 0; i<4;i++) {
		compositeTransform* lampTransform = new compositeTransform();
		lampTransform->add(new rotate(90*i,0,1,0));
		lampTransform->add(new translate(0,70.0,2));
		lampTransform->add(new rotate(45,1,0,0));
		add(new spotlamp(lampColours[i],lampColours[i],lampColours[i],lampColours[i],30.0,0.01,lampTransform, NULL));

		compositeTransform* teapotTransform = new compositeTransform();
		teapotTransform->add(new translate(0,2.5,0));
		teapotTransform->add(new rotate(90,0,1,0));
		add(new platformArm(new teapot(5,white,teapotTransform,NULL), new rotate(90*i,0,1,0)));
	}

	add(new cylinder(2.5,70.0,blue,new rotate(-90,1,0,0),NULL)); //center shaft

	add(new gear(25,4,new rotate(-90,1,0,0),NULL));

	
}

//--platformArm

platform::platformArm::platformArm(object* staticObject, transform* constTransform): objectgroup(constTransform, NULL) {
	add(new cube(3,3,25,grey,new translate(-1.5,30,0),NULL));

	objectgroup* plate = new objectgroup(new translate(0,35,25),NULL);

	compositeTransform* plateTransform = new compositeTransform();
	plateTransform->add(new translate(0,-2,0));
	plateTransform->add(new rotate(-90,1,0,0));
	plate->add(new cylinder(10,2,grey,plateTransform,NULL));

	if (staticObject != NULL) {
		plate->add(staticObject);
	}

	add(plate);
}