#ifndef H_ROTATEANIMATION
#define H_ROTATEANIMATION

#include "animation.h"

class rotateAnimation: public animation {
int x;
int y;
int z;
int direction;
float speedDPS;
float lastTheta;
public:
	static const unsigned short AXIS_X = 0x1;
	static const unsigned short AXIS_Y = 0x2;
	static const unsigned short AXIS_Z = 0x4;
	rotateAnimation(int direction, float speedDPS, unsigned short axis, float rotateOffset);
	virtual transform* animate(int deltaTMs);
};

#endif