#ifndef H_TRANSFORMS
#define H_TRANSFORMS

#include "main.h"

#include <list>
#include <GL/glut.h>

/**
 * Base transform class other transforms should inherit from
 */
class transform {
public:
	/**
	 * Apply the transform by calling the relevant methods (ie gl*)
	 * Should be overridden by subclasses
	 */
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
	float x;
	float y;
	float z;
public:
	translate(float x, float y, float z);
	translate(float target[3]);
	virtual void apply();
};

class rotate: public transform {
private:
	float theta;
	int x;
	int y;
	int z;
public:
	rotate(float theta, int x, int y, int z);
	rotate(float theta, unsigned short axis);
	virtual void apply();
};
#endif