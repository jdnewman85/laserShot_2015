#include <assert.h>
#include <stdio.h>

#include "bcm_host.h"
#include "openglMisc.h"

static StateGL_t _state, *state=&_state;

int main(int argNum, char** args) {
	printf("Number of arguements: %d\n", argNum);
	for(int i = 0; i < argNum; i++) {
		printf("Arg %d: %s\n", i, args[i]);
	}

	printf("initGL\n");

	initGL(state);
	debugSetupGL(state);

	//Test load a png
	TextureGL_t* myTexture;
	myTexture = loadTexture("./img/test.png");
	checkGL()
	printf("Images, bitches\n");

	//TEMP TEXTURE SHIT
	GLint texLoc;
	texLoc = glGetUniformLocation(state->program, "Texture");
	checkGL()
	//assert(texLoc >= 0);

	glActiveTexture(GL_TEXTURE0); //OPT NEEDED?
	checkGL()
	glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
	checkGL()
	glUniform1i(texLoc, 0);
	checkGL()

	for(;;) {
		drawScreenQuadGL(state);
	}
       

	printf("End\n");

	return 0;
}
