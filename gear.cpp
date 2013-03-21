#include "gear.h"

//--Public--

gear::gear(int teeth, float thickness, transform* constTransform, animation* animationProvider): object(constTransform, animationProvider) {
    numTeeth = teeth;
    this->thickness = thickness;
}

void gear::draw(){
    debug("gear::draw()");
    float radius = getRadius(numTeeth);
    float angInc1 = 0.5/radius;
    float angInc2 = 0.8/radius;

    float angle = 0.0;

    colorV(grey);

    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < numTeeth; i++)
    {
        glVertex3f(radius*cos(angle), radius*sin(angle),0.0);
        glVertex3f(radius*cos(angle), radius*sin(angle),thickness);
        angle += angInc1;
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),0.0);
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),thickness);
        angle += angInc2;
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),0.0);
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),thickness);
        angle += angInc1;
        glVertex3f(radius*cos(angle), radius*sin(angle),0.0);
        glVertex3f(radius*cos(angle), radius*sin(angle),thickness);
        angle += 2.0*angInc1;
    }
    glEnd();


    glNormal3f(0,1,0);
	draw2D(0.0);
    glNormal3f(0,-1,0);
    draw2D(thickness);
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


void gear::draw2D(float depth) {
	float radius = getRadius(numTeeth);
    float angInc1 = 0.5/radius;
    float angInc2 = 0.8/radius;

    float angle = 0.0;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, depth);
    for(int i = 0; i < numTeeth; i++)
    {
        glVertex3f(radius*cos(angle), radius*sin(angle),depth);
        angle += angInc1;
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),depth);
        angle += angInc2;
        glVertex3f((radius+2.0)*cos(angle), (radius+2.0)*sin(angle),depth);
        angle += angInc1;
        glVertex3f(radius*cos(angle), radius*sin(angle),depth);
        angle += 2.0*angInc1;
    }
    glVertex3f(radius, 0.0, depth);
    glEnd();
}