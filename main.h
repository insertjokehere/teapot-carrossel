#ifndef H_MAIN
#define H_MAIN

#include <string>

#define ANIM_STEP_MSEC 10.0
#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) //from http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c

//Uncomment the following line to enable all debug messages
//#define DEBUG_ALL
//Or enable them selectively
//#define DEBUG_TRACE
#define DEBUG_FPS

void debug(std::string message);

#ifdef DEBUG_ALL
#define DEBUG_TRACE
#define DEBUG_FPS
#endif

#endif