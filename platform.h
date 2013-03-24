#ifndef H_PLATFORM
#define H_PLATFORM

#include "gear.h"
#include "primitives.h"
#include "objectgroup.h"
#include "rotateAnimation.h"

class platform: public objectgroup {
private:
	class platformBody: public objectgroup {
	public:
		platformBody(transform* constTransform, animation* animationProvider);
		virtual void initilize();
		virtual void drawself();
	};

	class platformArm : public objectgroup {
	public:
		platformArm(object* staticObject, transform* constTransform);
		virtual void drawself();
	};

public:
	platform(transform* constTransform, animation* animationProvider);
};

#endif