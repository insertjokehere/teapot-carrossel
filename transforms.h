#ifndef H_TRANSFORMS
#define H_TRANSFORMS

#include <list>
#include <GL/glut.h>

class transform {
public:
	virtual void apply() {};
};

class compositeTransform: public transform {
private:
	std::list<transform*> transforms;
public:
	compositeTransform();

	virtual void apply();
	void add(transform* newTransform);
};

class translate: public transform {
private:
	float x, y, z;
public:
	translate(float x, float y, float z);
	virtual void apply();
};
#endif