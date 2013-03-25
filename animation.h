#ifndef H_ANIMATION
#define H_ANIMATION

#include "transforms.h"
#include "main.h"

/**
 * Animation base class. Should be subclassed by all animations
 */
class animation {
private:
	transform* animationTransform;
	unsigned long msElapsed;
	unsigned int animLength;
	unsigned long offset;
public:
	/**
	 * Constructs a new animation with no offset, and without specifying the length of the animation
	 */
	animation();

	/**
	 * Constructs a new animation of a given length, offset by the given number of milliseconds 
	 */
	animation(unsigned long animLength, unsigned long offset);

	void calcAnim(int deltaTMs);

	/**
	 * Resets the total elapsed time counter back to its original offset, or 0 if no offset was given
	 */
	void reset();

	/**
	 * Sets the length of the animation
	 * @param animLength The length of the animation in milliseconds
	 */
	void setAnimLength(unsigned int animLength);
	/**
	 * @return Returns the length of the animation
	 */
	unsigned int getAnimLength();

	/**
	 * Returns the transform that was calculated last time animate() was called
	 * Returns NULL if animate() has yet to be called
	 */
	transform* getAnimationTransform();

	/**
	 * @return Gets the total number of milliseconds that have elapsed, scaled for the offset.
	 * If the animation length is known, the value will be between 0 and the length
	 */
	unsigned long getTotalMsElapsed();

	/**
	 * Calculates the transform that this animation represents at the current time.
	 * Should be overridden by subclasses
	 * @param  deltaTMs the number of milliseconds since the last animate() call
	 * @return          a transform, or NULL if no transform should be applied
	 */
	virtual transform* animate(int deltaTMs) { return NULL; };
};

/**
 * A compound animation, plays a sequence of other animations
 */
class animationSequence: public animation {
private:
	std::list<unsigned int>* offsets;
	std::list<animation*>* animations;

	void construct();

	animation* lastAnim;
public:
	/**
	 * Constructs a new animationSequence that will start from t=0
	 */
	animationSequence();

	/**
	 * Constructs a new animationSequence, offset at the given number of milliseconds into the loop
	 */
	animationSequence(unsigned int offset);

	/**
	 * Adds a new animation to the end of this sequence
	 * @param animationProvider The animation to add
	 * @param lengthMs          The number of milliseconds the animation should play for, before
	 *                          the next animtion is played or the sequence loops if this is the
	 *                          last animation in the sequence
	 */
	void add(animation* animationProvider, unsigned int lengthMs);
	virtual transform* animate(int deltaTMs);
};

/**
 * A 'dummy' animation that transforms the object it is attached to by a constant value
 */
class staticAnimation: public animation {
private:
	transform* constTransform;
public:
	staticAnimation(transform* constTransform);
	virtual transform* animate(int deltaTMs);
};

/**
 * A 'dummy' animation that hides the object it is attached to by translating it through
 * the floor plane
 */
class hideObject: public animation {
public:
	hideObject();
	virtual transform* animate(int deltaTMs);
};
#endif