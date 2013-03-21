using namespace std;

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "colours.h"
#include "object.h"
#include "objectgroup.h"

#include "gear.h"
#include "floor.h"

#define ANIM_STEP_MSEC 10.0
#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) //from http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c

GLUquadric *q = gluNewQuadric();


float lgt_pos[] = {0.,50.,0.,1.};
float cameraPosition[] = {0, 50, 200};

float cameraAngle = 0;

object* rootobject;

void initialize(void) 
{

  rootobject = new objectgroup();

  rootobject.add(new gear(25, 10, 1, 1.0, 0));
  rootobject.add(new gear(15, 5, -1, 25.0/15.0, 10));
  rootobject.add(new gear(10, 5, -1, 25.0/10.0, 0));
  rootobject.add(new floorplane());

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

  rootobject.initialize();

  //spotlight
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
  //
  
  
}

//-------------------------------------------------------------------
void display(void)
{

   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt (cameraPosition[0], cameraPosition[1], cameraPosition[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


   glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);

   /*glTranslatef(0,50,0);
  
  glPushMatrix();
  glColor3f(0.0, 0.0, 1.0); 
  objects[0]->draw();
  glPopMatrix();
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); 
    glTranslatef(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0);
    objects[1]->draw();
  glPopMatrix();
  glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); 
    glTranslatef(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0);
    objects[2]->draw();
  glPopMatrix();*/

    rootobject.draw();

   glutSwapBuffers();
}

/**
 * glutTimerCallback(int value)
 * Callback function for glutTimer
 * Used to update animations
 */
void glutTimerCallback(int value) {

  rootobject->animate(ANIM_STEP_MSEC/1000.0);

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