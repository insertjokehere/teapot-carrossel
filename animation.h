#ifndef H_ANIMATION
#define H_ANIMATION

#include "transforms.h"
#include "main.h"

class animation {
private:
	transform* animationTransform;
	unsigned long msElapsed;
	unsigned int animLength;
	unsigned long offset;
protected:
	unsigned long getTotalMsElapsed();
public:
	animation();
	animation(unsigned int animLength, unsigned int offset);

	void calcAnim(int deltaTMs);

	void reset();

	void setAnimLength(unsigned int animLength);
	unsigned int getAnimLength();

	transform* getAnimationTransform();
	unsigned long totalMsElapsed();

	virtual transform* animate(int deltaTMs) { return NULL; };
};

class compositeAnimation: public animation {
private:
	std::list<unsigned int>* offsets;
	std::list<animation*>* animations;

	void construct();

	animation* lastAnim;
public:
	compositeAnimation();
	compositeAnimation(unsigned int offset);
	void add(animation* animationProvider, unsigned int lengthMs);
	virtual transform* animate(int deltaTMs);
};

class staticAnimation: public animation {
private:
	transform* constTransform;
public:
	staticAnimation(transform* constTransform);
	virtual transform* animate(int deltaTMs);
};

class hideObject: public animation {
public:
	hideObject();
	virtual transform* animate(int deltaTMs);
};
#endif