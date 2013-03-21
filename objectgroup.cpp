#include "objectgroup.h"

objectgroup::objectgroup(transform* constTransform, animation* animationProvider) : object(constTransform, animationProvider) {
	objects = std::list<object*>();
}

void objectgroup::draw() {
	debug("objectgroup::draw()");
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->transformAndDraw();
	}
}

void objectgroup::initilize() {
	debug("objectgroup::initilize()");
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->initilize();
	}
}

void objectgroup::animate(int deltaTMs) {
	debug("objectgroup::animate()");
	object::animate(deltaTMs);
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->animate(deltaTMs);
	}
}

void objectgroup::add(object* other) {
	objects.insert(objects.end(), other);
}