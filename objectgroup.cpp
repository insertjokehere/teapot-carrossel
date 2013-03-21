#include "objectgroup.h"

objectgroup::objectgroup() {
	objects = std::list<object*>();
}

void objectgroup::draw() {
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->draw();
	}
}

void objectgroup::initilize() {
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->initilize();
	}
}

void objectgroup::animate(float deltaT) {
	for (std::list<object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->animate(deltaT);
	}
}

void objectgroup::add(object* other) {
	objects.insert(objects.end(), other);
}