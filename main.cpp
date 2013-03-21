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

float cameraAngle = 0;

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

  gluLookAt (cameraPosition[0], cameraPosition[1], cameraPosition[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


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

  cameraAngle += 0.01;

  cameraPosition[0] = 200 * sin(cameraAngle);
  cameraPosition[2] = 200 * cos(cameraAngle);

  glutPostRedisplay();
  glutTimerFunc(ANIM_STEP_MSEC, glutTimerCallback, 0);
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

  glutMainLoop();
  return 0;
}