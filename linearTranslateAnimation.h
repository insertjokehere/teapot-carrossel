#ifndef H_LINEARTRANSLATEANIMATION
#define H_LINEARTRANSLATEANIMATION

#include "animation.h"

class linearTranslateAnimation: public animation {
private:
	float source[3];
	float target[3];
	float interpolate(float from, float to, float t);
public:
	linearTranslateAnimation(float source[3], float target[3], unsigned int moveTimeMs, unsigned int offset);
	virtual transform* animate(int deltaTMs);
};

#endif