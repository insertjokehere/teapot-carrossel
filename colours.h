#ifndef H_COLOURS
#define H_COLOURS

#include <GL/glut.h>

const float grey[4] = {0.2, 0.2, 0.2, 1.}; //ambient light
const float white[4] = {1.0, 1.0, 1.0, 1.};
const float black[4] = {0,0,0,0};
const float blue[4] = {0,0,1.0,1.};
const float red[4] = {1.0,0,0,1.0};
const float green[4] = {0,1.0,0,1.0};
const float orange[4] = {1.0,255.0/168.0,0.0,1.0};

void colorV(const float colour[4]);

#endif