#ifndef H_ROTATEANIMATION
#define H_ROTATEANIMATION

#include "animation.h"

class rotateAnimation: public animation {
int x;
int y;
int z;
int direction;
float speedDPS;
float rotateOffset;
public:
	rotateAnimation(int direction, float speedDPS, unsigned short axis, float rotateOffset);
	virtual transform* animate(int deltaTMs);
};

#endif