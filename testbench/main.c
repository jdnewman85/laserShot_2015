
//Still need to have textures and uniforms bound with a drawable
//Note, not all uniforms need to be updated every object





#include <stdio.h>

#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "../include/argon.h"

static arGlState _state, *state=&_state;

int main(int argNum, char** args) {
	printf("Number of arguments: %d\n", argNum);
	for(int i = 0; i < argNum; i++) {
		printf("Arg %d: %s\n", i, args[i]);
	}

	printf("initGL\n");

	//TODO Maybe arGraphics returns the state?
	arGraphics(state); //TODO Add the inits to arGraphics
	arSimpleSpriteInit(state);
	arAssertGl();

	//kazmath test
	kmVec2 point;
	kmMat3 transform;
	kmMat3 temp;

	kmVec2Fill(&point, 2.0f, 5.0f);
	kmMat3FromTranslation(&transform, -4.0f, -10.0f);
	kmMat3FromRotationZ(&temp, kmPI/2.0f);
	kmMat3MultiplyMat3(&transform, &temp, &transform);
	kmMat3FromScaling(&temp, 2.0f, 1.0f);
	kmMat3MultiplyMat3(&transform, &temp, &transform);

	kmVec2Transform(&point, &point, &transform);
	printf("Point{X: %f, Y: %f}\n", point.x, point.y);

	//Test load a png
	arTexture* myTexture;
	myTexture = arLoadTexture("./img/test.png");
	arAssertGl();
	printf("Images, bitches\n");

	//TEMP TEXTURE SHIT
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	arAssertGl();

	//Make Some Sprites
	arSimpleSprite* sprite1;
	sprite1 = arCreateSimpleSprite(myTexture);
	kmVec2Fill(&(sprite1->position), 100.0f, 100.0f);
	arSimpleSprite_UpdateModel(sprite1);

	arSimpleSprite* sprite2;
	sprite2 = arCreateSimpleSprite(myTexture);
	kmVec2Fill(&(sprite2->position), state->displayWidth/2 - 250, state->displayHeight/2 - 250);
	arSimpleSprite_UpdateModel(sprite2);

	for(;;) {
		arCls();

		arSimpleSprite_Draw(sprite1);
		arSimpleSprite_Draw(sprite2);

		glFlush();
		glFinish();
		arFlip(state);
	}
       

	printf("End\n");

	return 0;
}

