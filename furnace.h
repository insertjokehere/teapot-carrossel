#ifndef H_FURNACE
#define H_FURNACE

#include "main.h"
#include "objectgroup.h"
#include "colours.h"
#include "primitives.h"
#include "oscillateAnimation.h"

class furnace: public objectgroup {
private:
	class furnaceTop: public objectgroup {
	private:
		static const float frontFace[][3];
		static const float sides[][3];
		static const float top[][3];
	public:
		furnaceTop(transform* constTransform, animation* animationProvider);
		virtual void drawSelf();
	};

public:
	furnace(transform* constTransform, animation* animationProvider);
};

#endif