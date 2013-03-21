#ifndef H_OBJECT
#define H_OBJECT

#define NO_LIGHTS_AVALIBLE -1

#include "main.h"
#include "transforms.h"
#include "animation.h"

#include <GL/glut.h>

typedef unsigned int LIGHTID;

class object {
private:
	static int numLights;
	static LIGHTID lights[];

protected:
	transform* constTransform;
	animation* animationProvider;
public:
	object(transform* constTransform, animation* animationProvider);

	virtual void initilize() {};
	virtual void draw() {};
	virtual void animate(int deltaT);

	void transformAndDraw();

	static LIGHTID reserveLight();
};

#endif