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
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	arAssertGl();

	//Make Some Sprites
	arSimpleSprite* sprite1;
	sprite1 = arCreateSimpleSprite();
	sprite1->position.x = 100.0f;
	sprite1->position.y = 100.0f;
	sprite1->size.x = 100.0f;
	sprite1->size.y = 100.0f;
	arSimpleSprite_UpdateQuad(sprite1);

	arSimpleSprite* sprite2;
	sprite2 = arCreateSimpleSprite();
	sprite2->position.x = state->displayWidth/2 - 250;
	sprite2->position.y = state->displayHeight/2 - 250;
	sprite2->size.x = 500;
	sprite2->size.y = 500;
	arSimpleSprite_UpdateQuad(sprite2);

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

