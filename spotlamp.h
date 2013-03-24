#ifndef H_SPOTLAMP
#define H_SPOTLAMP

#include "object.h"
#include "main.h"
#include "colours.h"

class spotlamp: public object {
private:
	const float* colour;
	const float* ambient;
	const float* diffuse;
	const float* specular;
	float spot_cutoff;
	float spot_exponent;

	LIGHTID light;
public:
	spotlamp(const float* colour, const float* ambient, const float* diffuse, const float* specular, float spot_cutoff, float spot_exponent, transform* constTransform, animation* animationProvider);
	virtual void draw();
	virtual void initilize();
};

#endif