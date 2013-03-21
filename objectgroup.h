#ifndef H_OBJECTGROUP
#define H_OBJECTGROUP

#include <list>
#include "object.h"

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