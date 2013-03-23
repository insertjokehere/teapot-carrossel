#ifndef H_OSCILLATEANIMATION
#define H_OSCILLATEANIMATION

#include "animation.h"
#include "linearTranslateAnimation.h"

class oscillateAnimation: public compositeAnimation {
public:
	oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset);
};

#endif