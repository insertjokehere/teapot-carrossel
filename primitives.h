#ifndef H_PRIMITIVES
#define H_PRIMITIVES

#include <GL/glut.h>

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
	cube(float height, float width, float depth, const float* colour, transform* constTransform, animation* animationProvider);

	virtual void draw();
};

#endif