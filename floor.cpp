#include "floor.h"

void floor::draw() {
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	glColor4f(0.5, 0.5, 0.5, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	for(int i = -200; i < 200; i++)
	{
		for(int j = -200;  j < 200; j++)
		{
		glVertex3i(i, 0.0, j);
		glVertex3i(i, 0.0, j+1);
		glVertex3f(i+1, 0.0, j+1);
		glVertex3f(i+1, 0.0, j);
		}
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}