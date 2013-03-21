
#define IDENTITY_MATRIX {1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1}


class matrix {
private:
	float* innerMatrix[16];
public:
	matrix(float mxDef[16]);

	const matrix operator*(const matrix& other);
	
	float* getInnerMatrix();

	static matrix getTranslationMatrix(float x, float y, float z);
};