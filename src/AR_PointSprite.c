#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in AR_PointSprite.h

#include "AR_Vao.h"
#include "AR_Debug.h"
#include "AR_PointSprite.h"

//OPT COULD MAYBE MAKE THIS WHOLE THING INTO A CLASS IT'S OWN
//USE MAP FOR ATTRIBUTES?

static GLuint ShaderProgram;
static AR_Vao* Vao;
static GLuint Buffer; //OPT Better variable names?

void AR_PointSpriteInit() {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	
	//Load Shader
	ShaderProgram = AR_LoadShaderProgram("./shader/PointSprite");

	//Find Attributes //OPT Would be nice to use layout, or Bind before linking
	GLuint positionAttribLoc;
	positionAttribLoc = glGetAttribLocation(ShaderProgram, "position");

	//Alocate a buffer
	glGenBuffers(1, &Buffer);
	
	//Setup Attributes
	Vao = AR_CreateVao();
	AR_Vao_SetAttribute(Vao, positionAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(AR_PointSprite), (GLvoid*)offsetof(AR_PointSprite, x));
}

AR_PointSprite* AR_CreatePointSprites(int count) {
	AR_PointSprite* newPointSprite;
	newPointSprite = (AR_PointSprite*)malloc(sizeof(AR_PointSprite)*count);

	for(int i = 0; i < count; i++) {
		newPointSprite[i].x = 0.0f;
		newPointSprite[i].y = 0.0f;
	}

	return newPointSprite;
}

void AR_PointSprite_Draw(AR_PointSprite* simpleSprite, int count) {
	glUseProgram(ShaderProgram); //TODO OPT Change to use shader object later?
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	AR_Vao_Bind(Vao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(AR_PointSprite)*count, simpleSprite, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, count);

	//OPT Need?, debug only?
	AR_Vao_Bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

