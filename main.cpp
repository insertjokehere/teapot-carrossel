using namespace std;

#include "main.h"

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdio>


#include "colours.h"
#include "transforms.h"
#include "animation.h"
#include "object.h"
#include "objectgroup.h"

#include "rotateAnimation.h"

#include "floor.h"
#include "furnace.h"
#include "platform.h"

GLUquadric *q = gluNewQuadric();

float lgt_pos[] = {0.,50.,0.,1.};
float cameraPosition[] = {0, 50, 200};
float lookAt[] = {0, 50, 0};

int currentTime = 0;
int previousTime = 0;
int frameCount = 0;

int numLights = 0;
LIGHTID lights[] = {GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7}; //GL_LIGHT0 is reserved for global illumination

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

void configLight(LIGHTID light, const float ambient[4], const float diffuse[4], const float specular[4]) {
  glEnable(light);
  glLightfv(light, GL_AMBIENT, ambient);
  glLightfv(light, GL_DIFFUSE, diffuse);
  glLightfv(light, GL_SPECULAR, specular);
}

void configSpotLight(LIGHTID light, const float ambient[4], const float diffuse[4], const float specular[4], float spot_cutoff, float spot_exponent) {
  configLight(light, ambient, diffuse, specular);
  glLightf(light, GL_SPOT_CUTOFF, spot_cutoff);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,spot_exponent);
}

LIGHTID reserveLight()  {
  if (NELEMS(lights) == numLights - 1) {
    //all the lights have been reserved
    return NO_LIGHTS_AVALIBLE;
  } else {
    LIGHTID light = lights[numLights];
    numLights++;
    return light;
  }
}

void initialize(void) 
{

  rootobject = new objectgroup(NULL, NULL);

  rootobject->add(new furnace(new rotate(180,0,1,0), NULL));
  rootobject->add(new platform(new translate(0,0,40),NULL));
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

  configLight(GL_LIGHT0, grey, white, white);

  rootobject->initilize();

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