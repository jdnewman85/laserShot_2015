#include <stdio.h>

#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "../include/argon.h"

static arGlState _state, *state=&_state;

int main(int argNum, char** args) {
	printf("Number of arguements: %d\n", argNum);
	for(int i = 0; i < argNum; i++) {
		printf("Arg %d: %s\n", i, args[i]);
	}

	printf("initGL\n");

	arGraphics(state); //TODO Add the inits to arGraphics
	arSimpleSpriteInit();

	//kazmath test
	kmVec3 testVector;
	kmMat4 testMatrix;
	kmMat4RotationZ(&testMatrix, kmPI/2.0f);
	testVector.x = 10.0f;
	testVector.y = 1.111f;
	printf("testVector: (x%f, y%f, z%f)\n", testVector.x, testVector.y, testVector.z);
	kmVec3Transform(&testVector, &testVector, &testMatrix);
	printf("testVector: (x%f, y%f, z%f)\n", testVector.x, testVector.y, testVector.z);

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
	sprite1->position.x = 0.0f;
	sprite1->position.y = 0.0f;
	sprite1->size.x = 0.5f;
	sprite1->size.y = 0.5f;
	arSimpleSprite_UpdateQuad(sprite1);

	arSimpleSprite* sprite2;
	sprite2 = arCreateSimpleSprite();
	sprite2->position.x = -0.5f;
	sprite2->position.y = -0.5f;
	sprite2->size.x = 0.5f;
	sprite2->size.y = 0.5f;
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

