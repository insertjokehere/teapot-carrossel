#ifndef H_PLATFORM
#define H_PLATFORM

#include "objectgroup.h"

class platform: public objectgroup {
private:
	class platformBody: public objectgroup {
	public:
		platformBody();
		virtual void initilize();
		virtual void drawself();
	};

	class platformArm : public objectgroup {
	public:
		platformArm(object* staticObject, transform* constTransform);
		virtual void drawself();
	};

public:
	virtual void drawself();
};

#endif