#ifndef H_ANIMATION
#define H_ANIMATION

#include "transforms.h"
#include "main.h"

class animation {
private:
	transform* animationTransform;
	unsigned long msElapsed;
protected:
	unsigned long getTotalMsElapsed();
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

class compositeAnimation: public animation {
private:
	std::list<unsigned int>* offsets;
	std::list<animation*>* animations;

	unsigned int offset;
	unsigned int totalTime;

	void construct(unsigned int offset);
public:
	compositeAnimation();
	compositeAnimation(unsigned int offset);
	void add(animation* animationProvider, unsigned int lengthMs);
	virtual transform* animate(int deltaTMs);
};

class linearTranslateAnimation: public animation {
public:
	linearTranslateAnimation(float source[3], float target[3], unsigned int moveTimeMs, unsigned int offset);
};

class staticAnimation: public animation {
private:
	transform* constTransform;
public:
	staticAnimation(transform* constTransform);
	virtual transform* animate(int deltaTMs);
};

class oscillateAnimation: public compositeAnimation {
public:
	oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset);
};
#endif