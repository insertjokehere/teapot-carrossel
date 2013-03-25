#ifndef H_MAIN
#define H_MAIN

#include <string>

#define ANIM_STEP_MSEC 10.0
#define NO_LIGHTS_AVALIBLE -1
#define CAMERA_ROTATE_STEP 5

#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) //from http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c

typedef unsigned int LIGHTID;

//Uncomment the following line to enable all debug messages
//#define DEBUG_ALL
//Or enable them selectively
//#define DEBUG_TRACE
#define DEBUG_FPS

void debug(std::string message);
void debug(float message);

float toRads(float degs);

LIGHTID reserveLight();
void configLight(LIGHTID light, const float ambient[4], const float diffuse[4], const float specular[4]);
void configSpotLight(LIGHTID light, const float ambient[4], const float diffuse[4], const float specular[4], float spot_cutoff, float spot_exponent);

static const unsigned short AXIS_X = 0x1;
static const unsigned short AXIS_Y = 0x2;
static const unsigned short AXIS_Z = 0x4;

#define CAMERA_MODE_FREE 0
#define CAMERA_MODE_FIXED 1

int getCameraMode();
void setCameraMode(int mode);

#ifdef DEBUG_ALL
#define DEBUG_TRACE
#define DEBUG_FPS
#endif

#endif