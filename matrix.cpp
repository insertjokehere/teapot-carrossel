#include "matrix.h"

matrix::matrix() {
	float identity[16] = IDENTITY_MATRIX;
	innerMatrix = identity;
}

matrix::matrix(float mxDef[16]) {
	innerMatrix = mxDef;
}

float* matrix::getInnerMatrix() {
	return innerMatrix;
}

matrix* matrix::operator*(matrix* other) {
	float newMatrix[16] = { 0,0,0,0,
							0,0,0,0,
							0,0,0,0,
							0,0,0,0};

	for (int row=0; row<4; row++) {
		for (int column=0; column<4; column++) {
			newMatrix[(row*4)+column] = innerMatrix[row] * other->getInnerMatrix()[column];
		}
	}

	return new matrix(newMatrix);
}

matrix* matrix::getTranslationMatrix(float x, float y, float z) {
	float newMatrix[16] = {1,0,0,x,
					   	   0,1,0,y,
					       0,0,1,z,
					       0,0,0,1};

	return new matrix(newMatrix);
}

matrix* matrix::getIdentityMatrix() {
	float newMatrix[16] = IDENTITY_MATRIX;

	return new matrix(newMatrix);
}