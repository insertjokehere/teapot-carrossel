const float PI = 3.141593f;
const float SPACING = 2.5;

class gear: public object {
private:
	int numTeeth;
	float speed;
	float position;
	int direction;
	float thickness;

	static float getRadius(int numTeeth);
	void draw2D();
public:
	gear(int teeth, float thickness, int rotateDir, float rotateSpeed, float rotateOffset);
	virtual void draw();
	virtual void animate(float deltaT);
	static float distX(float theta, int gear1, int gear2);
	static float distY(float theta, int gear1, int gear2);
};