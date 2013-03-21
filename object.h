#ifndef H_OBJECT
#define H_OBJECT

#define NO_LIGHTS_AVALIBLE -1

#include "matrix.h"
#include "main.h"

#include <GL/glut.h>

typedef unsigned int LIGHTID;

class object {
private:
	static int numLights;
	static LIGHTID lights[];

	void construct(matrix* transform);
protected:
	matrix* transformationMatrix;
public:
	object(matrix* transform);
	object();

	virtual void initilize() {};
	virtual void draw() {};
	virtual void animate(float deltaT) {};

	void transformAndDraw();

	static LIGHTID reserveLight();
};

#endif