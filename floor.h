#ifndef H_FLOOR
#define H_FLOOR

#include "colours.h"
#include "object.h"
#include "main.h"

#include <GL/glut.h>

class floorplane: public object {
private:
public:
	virtual void draw();
};

#endif