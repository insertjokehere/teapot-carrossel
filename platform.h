#ifndef H_PLATFORM
#define H_PLATFORM

#include "gear.h"
#include "primitives.h"
#include "objectgroup.h"
#include "rotateAnimation.h"
#include "linearTranslateAnimation.h"
#include "spotlamp.h"

class platform: public objectgroup {
private:
	class platformBody: public objectgroup {
	public:
		platformBody(transform* constTransform, animation* animationProvider);
	};

	class platformArm : public objectgroup {
	public:
		platformArm(int armNumber, object* staticObject, transform* constTransform);
	};

public:
	platform(transform* constTransform, animation* animationProvider);
};

#endif