#ifndef H_OBJECT
#define H_OBJECT

#define NO_LIGHTS_AVALIBLE -1

#include "main.h"
#include "transforms.h"

#include <GL/glut.h>

typedef unsigned int LIGHTID;

class object {
private:
	static int numLights;
	static LIGHTID lights[];

	void construct(transform* constTransform);
protected:
	transform* constTransform;
public:
	object(transform* constTransform);
	object();

	virtual void initilize() {};
	virtual void draw() {};
	virtual void animate(float deltaT) {};

	void transformAndDraw();

	static LIGHTID reserveLight();
};

#endif