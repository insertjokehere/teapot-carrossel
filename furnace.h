#include "object.h"

class furnace: public object {
private:
public:
	furnace();
	virtual void draw();
	virtual void animate(float deltaT);
	virtual void initilize();
};