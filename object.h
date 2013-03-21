#define NO_LIGHTS_AVALIBLE -1
#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) //from http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c

typedef unsigned int LIGHTID;

class object {
private:
	static int numLights;
	static LIGHTID lights[];
public:
	virtual void initilize() {};
	virtual void draw() {};
	virtual void animate(float deltaT) {};

	static LIGHTID reserveLight();
};