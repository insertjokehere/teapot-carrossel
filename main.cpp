using namespace std;

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdio>

#include "main.h"
#include "colours.h"
#include "object.h"
#include "objectgroup.h"
#include "transforms.h"
#include "animation.h"

#include "gear.h"
#include "floor.h"

GLUquadric *q = gluNewQuadric();

float lgt_pos[] = {0.,50.,0.,1.};
float cameraPosition[] = {0, 50, 200};
float lookAt[] = {0, 50, 0};

int currentTime = 0;
int previousTime = 0;
int frameCount = 0;

objectgroup* rootobject;

void debug(std::string message) {
  #ifdef DEBUG_TRACE
  cout << message << endl;
  #endif
}

void debug(float message) {
  #ifdef DEBUG_TRACE
  cout << message << endl;
  #endif
}

void initialize(void) 
{

  rootobject = new objectgroup(NULL, NULL);

  objectgroup* gears = new objectgroup(new translate(0,50,0), NULL);
  gears->add(new gear(25, 10, NULL, new rotateAnimation(1.0, 90, rotateAnimation::AXIS_Z, 0.0)));
  gears->add(new gear(15, 5, new translate(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0), new rotateAnimation(-1.0, 25.0/15.0 * 90, rotateAnimation::AXIS_Z, 10)));
  gears->add(new gear(10, 5,  new translate(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0), new rotateAnimation(-1.0, 25.0/10.0 * 90, rotateAnimation::AXIS_Z, 0)));

  rootobject->add(gears);
  rootobject->add(new floorplane());

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  gluQuadricDrawStyle(q, GLU_FILL);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection


  glEnable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);  

  //global lighting
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);

  rootobject->initilize();

  //spotlight
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
  //


}

void calcFPS() { //from http://mycodelog.com/2010/04/16/fps/
  //  Increase frame count
  frameCount++;

  //  Get the number of milliseconds since glutInit called
  //  (or first call to glutGet(GLUT ELAPSED TIME)).
  currentTime = glutGet(GLUT_ELAPSED_TIME);

  //  Calculate time passed
  int timeInterval = currentTime - previousTime;

  if(timeInterval > 1000)
  {
    //  calculate the number of frames per second
    int fps = frameCount / (timeInterval / 1000.0f);

    //  Set time
    previousTime = currentTime;

    //  Reset frame count
    frameCount = 0;

    cout << "FPS: " << fps << endl;
  }
}

//-------------------------------------------------------------------
void display(void)
{

  debug("display()--");

  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt (cameraPosition[0],cameraPosition[1],cameraPosition[2],lookAt[0],lookAt[1],lookAt[2],0.0,1.0,0.0);
  
  glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);

  glPushMatrix();
  rootobject->transformAndDraw();
  glPopMatrix();

  glutSwapBuffers();

  debug("---");

  #ifdef DEBUG_FPS

  calcFPS();

  #endif
}

/**
* glutTimerCallback(int value)
* Callback function for glutTimer
* Used to update animations
*/
void glutTimerCallback(int value) {

  rootobject->animate(ANIM_STEP_MSEC);

  /*cameraAngle += 0.01;

  cameraPosition[0] = 200 * sin(cameraAngle);
  cameraPosition[2] = 200 * cos(cameraAngle);*/

  glutPostRedisplay();
  glutTimerFunc(ANIM_STEP_MSEC, glutTimerCallback, 0);
}

void rotatePoint(float origin[3], float point[3], float angle) {
  float s = sin(toRads(angle));
  float c = cos(toRads(angle));

  point[0] = c * (point[0] - origin[0]) - s * (point[2] - origin[2]) + origin[0];
  point[2] = s * (point[0] - origin[0]) + c * (point[2] - origin[2]) + origin[2];
}

float fAbs(float val) {
  if (val < 0) {
    return val * -1.0;
  } else {
    return val;
  }
}

void translatePoints(float a[3], float b[3], float incr) {
  float xStep;
  float zStep;
  float xIncr = incr;
  float zIncr = incr;

  debug("translatePoints");

  if (a[0] < b[0]) {
    xStep = a[0] - b[0];
    xIncr = xIncr * -1;
  } else {
    xStep = b[0] - a[0];
  }

  if (a[2] < b[2]) {
    zStep = a[2] - b[2];
    zIncr = zIncr * -1;
  } else {
    zStep = b[2] - a[2];
  }

  float theta = atan(xStep/zStep);
  float deltaX = sin(theta) * xIncr;
  float deltaZ = cos(theta) * zIncr;

  a[0] += deltaX;
  b[0] += deltaX;

  a[2] += deltaZ;
  b[2] += deltaZ;

  debug(deltaX);
  debug(deltaZ);

  debug(xStep);
  debug(zStep);

  debug(a[0]);
  debug(a[2]);

  debug(b[0]);
  debug(b[2]);

}

void glutSpecialCallback(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
    {
      debug("GLUT_KEY_UP");
      translatePoints(cameraPosition, lookAt, -5);
    }
    break;
    case GLUT_KEY_DOWN:
    {
      debug("GLUT_KEY_DOWN");
      translatePoints(cameraPosition, lookAt, 5);
    }
    break;
    case GLUT_KEY_LEFT:
    {
      debug("GLUT_KEY_LEFT");
      rotatePoint(cameraPosition, lookAt, -CAMERA_ROTATE_STEP);
    }
    break;
    case GLUT_KEY_RIGHT:
    {
      debug("GLUT_KEY_RIGHT");
      rotatePoint(cameraPosition, lookAt, CAMERA_ROTATE_STEP);
    }
    break;
  }
}

float toRads(float degs) {
  return (degs / 180) * PI;
}

//---------------------------------------------------------------------
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
  glutInitWindowSize (600, 600); 
  glutInitWindowPosition (50, 50);
  glutCreateWindow (argv[0]);
  initialize ();

  glutDisplayFunc(display); 
  glutTimerFunc(ANIM_STEP_MSEC, glutTimerCallback, 0);
  glutSpecialFunc(glutSpecialCallback);

  glutMainLoop();
  return 0;
}