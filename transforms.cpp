#include "transforms.h"

compositeTransform::compositeTransform() {
	transforms = std::list<transform*>();
}

void compositeTransform::add(transform* newTransform) {
	transforms.insert(transforms.end(), newTransform);
}

void compositeTransform::apply() {
	for (std::list<transform*>::iterator it = transforms.begin(); it != transforms.end(); it++) {
		(*it)->apply();
	}
}

translate::translate(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void translate::apply() {
	glTranslatef(x, y, z);
}