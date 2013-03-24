#ifndef H_PRIMITIVES
#define H_PRIMITIVES

#include <GL/glut.h>
#include <math.h>

#include "object.h"
#include "animation.h"
#include "transforms.h"
#include "colours.h"
#include "main.h"

class cube: public object {
private:
	float height, width, depth;
	const float* colour;	

public:
	cube(float width, float height, float depth, const float* colour, transform* constTransform, animation* animationProvider);
	virtual void draw();
};

class cylinder: public object {
private:
	static const int slices = 20;
	const float* colour;
	float radius, length;
public:
	cylinder(float radius, float length, const float* colour, transform* constTransform, animation* animationProvider);
	virtual void draw();
};

class cone: public object {
private:
	static const int slices = 20;
	const float* colour;
	float baseRadius, length;
public:
	cone(float baseRadius, float length, const float* colour, transform* constTransform, animation* animationProvider);
	virtual void draw();
};

class teapot: public object {
private:
	float size;
	const float* colour;
public:
	teapot(float size, const float* colour, transform* constTransform, animation* animationProvider);
	virtual void draw();
};
#endif