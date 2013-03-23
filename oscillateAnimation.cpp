#include "oscillateAnimation.h"

oscillateAnimation::oscillateAnimation(float target[3], unsigned int moveTimeMs, unsigned int farHoldMs, unsigned int nearHoldMs, unsigned int offset): compositeAnimation(offset) {
	// |---moveTimeMs-------------|---farHoldMs-----|---moveTimeMs-------------|---nearHoldMs----|
	// | linearTranslateAnimation | staticAnimation | linearTranslateAnimation | staticAnimation |

	float origin[3] = {0,0,0};

	add(new linearTranslateAnimation(origin, target, moveTimeMs, 0), moveTimeMs);
	add(new staticAnimation(new translate(target)),farHoldMs);
	add(new linearTranslateAnimation(target, origin, moveTimeMs, 0), moveTimeMs);
	add(new staticAnimation(NULL), nearHoldMs);
}