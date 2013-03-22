#ifndef H_OBJECT
#define H_OBJECT

#include "main.h"
#include "transforms.h"
#include "animation.h"

#include <GL/glut.h>



class object {
protected:
	transform* constTransform;
	animation* animationProvider;
public:
	object(transform* constTransform, animation* animationProvider);

	virtual void initilize() {};
	virtual void draw() {};
	virtual void animate(int deltaT);

	void transformAndDraw();

	static void drawVertex(const float vertex[][3], unsigned int count, GLenum mode);
};

#endif