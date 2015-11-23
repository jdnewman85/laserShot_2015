#include <stdio.h>

#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "../include/Argon.h"

static StateGL_t _state, *state=&_state;

int main(int argNum, char** args) {
	printf("Number of arguements: %d\n", argNum);
	for(int i = 0; i < argNum; i++) {
		printf("Arg %d: %s\n", i, args[i]);
	}

	printf("initGL\n");

	AR_Graphics(state); //TODO Add the inits to AR_Graphics
//	AR_DebugInit(state);
	AR_SimpleSpriteInit();

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
	AR_Texture* myTexture;
	myTexture = AR_LoadTexture("./img/test.png");
	AR_CheckGL();
	printf("Images, bitches\n");

	//TEMP TEXTURE SHIT
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	AR_CheckGL();

	//Make Some Sprites
	AR_SimpleSprite* sprite1;
	sprite1 = AR_CreateSimpleSprite();

	sprite1->position.x = 0.0f;
	sprite1->position.y = 0.0f;

	for(;;) {
		AR_Cls();

		//AR_DebugDraw(state);
		AR_SimpleSprite_Draw(sprite1);


		glFlush();
		glFinish();
		AR_Flip(state);
	}
       

	printf("End\n");

	return 0;
}

