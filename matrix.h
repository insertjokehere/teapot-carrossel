#ifndef H_MATRIX
#define H_MATRIX

#define IDENTITY_MATRIX {1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1}


class matrix {
private:
	float* innerMatrix;
public:
	matrix();
	matrix(float mxDef[16]);

	matrix* operator*(matrix* other);
	
	float* getInnerMatrix();

	static matrix* getIdentityMatrix();

	static matrix* getTranslationMatrix(float x, float y, float z);
};

#endif