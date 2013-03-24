#include "trashBox.h"

trashbox::trashbox(transform* constTransform, animation* animationProvider) : objectgroup(constTransform, animationProvider) {
	compositeAnimation* fallingPotAnim = new compositeAnimation();
	float origin[] = {0,0,0};
	float ground[] = {-30,-30,0};
	fallingPotAnim->add(new hideObject(),1000);
	fallingPotAnim->add(new linearTranslateAnimation(origin,ground,200,0),200);
	fallingPotAnim->add(new hideObject(), 4800);

	compositeTransform* fallingPotTranform = new compositeTransform();
	fallingPotTranform->add(new translate(0,24,0));
	fallingPotTranform->add(new rotate(45,AXIS_X));
	fallingPotTranform->add(new rotate(90,AXIS_Y));

	add(new teapot(5,white,fallingPotTranform,fallingPotAnim));

}

void trashbox::drawSelf() {
	float boxVertex[][3] = { {-5,0,-5},{-5,7,-5},{-5,0,0},{-5,7,0},{0,0,0},{0,7,0},{0,0,-5},{0,7,-5},{-5,0,-5},{-5,7,-5}};
	drawVertex(boxVertex,10,GL_QUAD_STRIP);
}