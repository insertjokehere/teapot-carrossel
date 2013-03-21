#include "object.h"
#include "gear.h"

#include <GL/glut.h>
#include <math.h>

//--Public--

gear::gear(int teeth, int rotateDir, float rotateSpeed, float rotateOffset) {
	numTeeth = teeth;
	speed = rotateSpeed;
	position = rotateOffset;
	direction = rotateDir;
}

void gear::draw() {
	float radius = getRadius(numTeeth);
    float angInc1 = 0.5/radius;
    float angInc2 = 0.8/radius;

    float angle = 0.0;

    glRotatef(position, 0, 0, 1);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for(int i = 0; i < numTeeth; i++)
    {
        glVertex2f(radius*cos(angle), radius*sin(angle));
        angle += angInc1;
        glVertex2f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle));
        angle += angInc2;
        glVertex2f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle));
        angle += angInc1;
        glVertex2f(radius*cos(angle), radius*sin(angle));
        angle += 2.0*angInc1;
    }
    glVertex2f(radius, 0.0);
    glEnd();
}

void gear::animate(float deltaT) {
	position += (speed / deltaT) * direction;
}

float gear::distY(float theta, int gear1, int gear2) {
  float t = (theta/360.0) * (2 * PI); //convert to radians
  return sin(t) * float(getRadius(gear1) + getRadius(gear2) + SPACING);
}

float gear::distX(float theta, int gear1, int gear2) {
  float t = (theta/360.0) * (2 * PI); //convert to radians
  return cos(t) * float(getRadius(gear1) + getRadius(gear2) + SPACING);
}

//--Private--
float gear::getRadius(int numTeeth){
    return 1.4*numTeeth/PI;
}