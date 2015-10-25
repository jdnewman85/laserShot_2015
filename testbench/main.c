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

	//Test load a png
	AR_Texture* myTexture;
	myTexture = AR_LoadTexture("./img/test.png");
	checkGL();
	printf("Images, bitches\n");

	//TEMP TEXTURE SHIT
	GLint texLoc;
	texLoc = glGetUniformLocation(state->program, "Texture");
	checkGL();
	//assert(texLoc >= 0);

	glActiveTexture(GL_TEXTURE0); //OPT NEEDED?
	checkGL();
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	checkGL();
	glUniform1i(texLoc, 0);
	checkGL();

	for(;;) {
		AR_Cls();
		AR_DebugDraw(state);
	}
       

	printf("End\n");

	return 0;
}
