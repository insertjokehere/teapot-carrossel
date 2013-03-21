#include "objectgroup.h"

objectgroup::objectgroup() {
	objects = std::list<object*>();
}

objectgroup::objectgroup(matrix* transform) : object(transform) {
	objects = std::list<object*>();
}

void objectgroup::draw() {
	debug("objectgroup::draw()");
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->draw();
	}
}

void objectgroup::initilize() {
	debug("objectgroup::initilize()");
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->initilize();
	}
}

void objectgroup::animate(float deltaT) {
	debug("objectgroup::animate()");
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->animate(deltaT);
	}
}

void objectgroup::add(object* other) {
	objects.insert(objects.end(), other);
}