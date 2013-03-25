#ifndef H_TRASHBOX
#define H_TRASHBOX

#include "objectgroup.h"
#include "linearTranslateAnimation.h"
#include "primitives.h"

class trashbox: public objectgroup {
public:
	trashbox(transform* constTransform, animation* animationProvider);
};

#endif