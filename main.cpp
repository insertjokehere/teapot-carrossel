using namespace std;

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "object.h"
#include "gear.h"

#define ANIM_STEP_MSEC 10.0

GLUquadric *q = gluNewQuadric();

float grey[4] = {0.2, 0.2, 0.2, 1.}; //ambient light
float white[4] = {1.0, 1.0, 1.0, 1.};
float black[4] = {0,0,0,0};
float rot[] = {0,-10.5,-21.0,-31.5};

object* gear1;
object* gear2;
object* gear3;

void initialize(void) 
{

  gear1 = new gear(25, 1, 1.0, 0);
  gear2 = new gear(15, -1, 25.0/15.0, 10);
  gear3 = new gear(10, -1, 25.0/10.0, 0);

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

   gluLookAt (0, 50, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   float lgt_pos[] = {0.,50.,0.,1.};
   float spot_pos[] = {-10.,14.,0.,1.};
   float spot_look[] = {-4.,-4.,0.,1.};

   glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);


  glColor3f(0.0, 0.0, 1.0); 
  glPushMatrix();
  gear1->draw();
  glPopMatrix();
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); 
    glTranslatef(gear::distX(45.0, 25,15), gear::distY(45.0,25,15), 0);
    gear2->draw();
  glPopMatrix();
  glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); 
    glTranslatef(-gear::distX(45.0, 25,10), gear::distY(45.0,25,10), 0);
    gear3->draw();
  glPopMatrix();

   glutSwapBuffers();
}

/**
 * glutTimerCallback(int value)
 * Callback function for glutTimer
 * Used to update animations
 */
void glutTimerCallback(int value) {

  gear1->animate(ANIM_STEP_MSEC / 1000.0);
  gear2->animate(ANIM_STEP_MSEC / 1000.0);
  gear3->animate(ANIM_STEP_MSEC / 1000.0);

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