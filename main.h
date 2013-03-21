#ifndef H_MAIN
#define H_MAIN

#include <string>

#define ANIM_STEP_MSEC 10.0
#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) //from http://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c

//Uncomment the following line to enable debug messages
#define DEBUG
void debug(std::string message);

#endif