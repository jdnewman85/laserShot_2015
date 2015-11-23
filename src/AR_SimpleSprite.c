#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in AR_SimpleSprite.h

#include "AR_Vao.h"
#include "AR_Debug.h"
#include "AR_Misc.h"
#include "AR_SimpleSprite.h"

//OPT COULD MAYBE MAKE THIS WHOLE THING INTO A CLASS IT'S OWN
//USE MAP FOR ATTRIBUTES?

static GLuint ShaderProgram;
static AR_Vao* Vao;
static GLuint Buffer; //OPT Better variable names?

void AR_SimpleSpriteInit() {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	
	//Load Shader
	ShaderProgram = AR_LoadShaderProgram("./shader/SimpleSprite");

	//Find Attributes //OPT Would be nice to use layout, or Bind before linking
	GLuint vertPosAttribLoc;
	vertPosAttribLoc = glGetAttribLocation(ShaderProgram, "vertPos");

	//Alocate a buffer
	glGenBuffers(1, &Buffer);
	
	//Setup Attributes
	Vao = AR_CreateVao();
	AR_Vao_SetAttribute(Vao, vertPosAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, /*(GLvoid*)offsetof(AR_Vec2, x)*/ 0);
}

AR_SimpleSprite* AR_CreateSimpleSprite() {
	AR_SimpleSprite* this;
	this = (AR_SimpleSprite*)malloc(sizeof(AR_SimpleSprite));

	kmVec2Fill(&(this->position), 0.0f, 0.0f);
	kmVec2Fill(&(this->size), 100.0f, 100.0f);

	kmVec2* quad;
	quad = AR_CreateQuad();

	kmVec2Fill(&quad[0], -1.0f, -1.0f);
	kmVec2Fill(&quad[1],  1.0f, -1.0f);
	kmVec2Fill(&quad[2],  1.0f,  1.0f);
	kmVec2Fill(&quad[3], -1.0f,  1.0f);

	this->quad = quad;

	return this;
}

/*
void AR_SimpleSprite_UpdateQuad(AR_SimpleSprite* this) {
	//Calculate quad from sprite data
	
}
*/

void AR_SimpleSprite_Draw(AR_SimpleSprite* this) {
	glUseProgram(ShaderProgram); //TODO OPT Change to use shader object later?
	glBindBuffer(GL_ARRAY_BUFFER, Buffer); //TODO OPT ask for buffer?
	AR_Vao_Bind(Vao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(kmVec2)*4, this->quad, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//OPT Need?, debug only?
	AR_Vao_Bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

