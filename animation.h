#ifndef H_ANIMATION
#define H_ANIMATION

#include "transforms.h"
#include "main.h"

class animation {
private:
	transform* animationTransform;
	unsigned long msElapsed;
public:
	animation();
	void calcAnim(int deltaTMs);
	transform* getAnimationTransform();
	unsigned long totalMsElapsed();

	virtual transform* animate(int deltaTMs) { return NULL; };
};

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