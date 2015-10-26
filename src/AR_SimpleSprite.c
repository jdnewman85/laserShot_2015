#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in AR_SimpleSprite.h

#include "AR_Vao.h"
#include "AR_Debug.h"
#include "AR_SimpleSprite.h"

//OPT COULD MAYBE MAKE THIS WHOLE THING INTO A CLASS IT'S OWN
//USE MAP FOR ATTRIBUTES?

static GLuint ShaderProgram;
static AR_Vao* Vao;

void AR_SimpleSpriteInit() {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	
	//Load Shader
	ShaderProgram = AR_LoadShaderProgram("./shader/SimpleSprite");

	//Find Attributes //OPT Would be nice to use layout, or Bind before linking
	GLuint positionAttribLoc;
	positionAttribLoc = glGetAttribLocation(ShaderProgram, "position");
	
	//Setup Attributes
	Vao = AR_CreateVao();
	AR_Vao_SetAttribute(Vao, positionAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(AR_SimpleSprite), (GLvoid*)offsetof(AR_SimpleSprite, x));
}

AR_SimpleSprite* AR_CreateSimpleSprite() {
	AR_SimpleSprite* newSimpleSprite;
	newSimpleSprite = (AR_SimpleSprite*)malloc(sizeof(AR_SimpleSprite));

	newSimpleSprite->x = 0.0f;
	newSimpleSprite->y = 0.0f;

	return newSimpleSprite;
}

