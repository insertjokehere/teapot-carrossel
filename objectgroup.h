#ifndef H_OBJECTGROUP
#define H_OBJECTGROUP

#include "object.h"
#include "main.h"

#include <list>

class objectgroup: public object {
private:
std::list<object*> objects;
public:
	objectgroup(transform* transform, animation* animationProvider);
	virtual void draw();
	virtual void initilize();
	virtual void animate(int deltaTMs);
	virtual void drawSelf() {};
	void add(object* other);
};

#endif