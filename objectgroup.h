#ifndef H_OBJECTGROUP
#define H_OBJECTGROUP

#include "object.h"
#include "main.h"

#include <list>

class objectgroup: public object {
private:
std::list<object*> objects;
public:
	objectgroup();
	objectgroup(matrix* transform);
	virtual void draw();
	virtual void initilize();
	virtual void animate(float deltaT);
	void add(object* other);
};

#endif