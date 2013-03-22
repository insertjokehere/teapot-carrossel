#ifndef H_FURNACE
#define H_FURNACE

#include "main.h"
#include "objectgroup.h"
#include "colours.h"

class furnace: public object {
private:
	LIGHTID light;
	static const float frontFace[][3];
	static const float side1[][3];
	static const float side2[][3];
public:
	furnace(transform* constTransform, animation* animationProvider);
	virtual void draw();
	virtual void initilize();
};

#endif