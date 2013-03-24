#ifndef H_GEAR
#define H_GEAR

#include "object.h"
#include "main.h"
#include "transforms.h"
#include "colours.h"

#include <GL/glut.h>
#include <math.h>

const float PI = 3.141593f;

class gear: public object {
private:
	int numTeeth;
	float thickness;

	void draw2D(float depth);
	
public:
	const static float SPACING = 2.5;
	static float getRadius(int numTeeth);
	gear(int teeth, float thickness, transform* constTransform, animation* animationProvider);
	virtual void draw();
	static float distX(float theta, int gear1, int gear2);
	static float distY(float theta, int gear1, int gear2);
};

#endif