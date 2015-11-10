#include <stdio.h>

#include <GLES2/gl2.h>

#include "../include/Argon.h"

static StateGL_t _state, *state=&_state;

int main(int argNum, char** args) {
	printf("Number of arguements: %d\n", argNum);
	for(int i = 0; i < argNum; i++) {
		printf("Arg %d: %s\n", i, args[i]);
	}

	printf("initGL\n");

	AR_Graphics(state);
	AR_DebugInit(state);

	//Test Load of Sprite stuffs
	AR_SimpleSpriteInit();

	//Test load a png
	AR_Texture* myTexture;
	myTexture = AR_LoadTexture("./img/test.png");
	AR_CheckGL();
	printf("Images, bitches\n");

	//TEMP TEXTURE SHIT
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	AR_CheckGL();

	//Make Some Sprites
	AR_SimpleSprite* mySprites;
	mySprites = AR_CreateSimpleSprites(5);

	for(int i = 0; i < 5; i++) {
		mySprites[i].x = 0.2f*i;
		mySprites[i].y = 0.0f;
	}

	for(;;) {
		AR_Cls();

		//AR_DebugDraw(state);
		AR_SimpleSprite_Draw(mySprites, 5);


		glFlush();
		glFinish();
		AR_Flip(state);
	}
       

	printf("End\n");

	return 0;
}

