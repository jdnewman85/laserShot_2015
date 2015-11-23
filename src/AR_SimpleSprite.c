#include <assert.h>
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
static GLuint VertexBuffer; //OPT Better variable names?
static GLuint TextureCoordBuffer;

static kmVec2* TextureCoordData; //TODO Does this really need to be global?

void AR_SimpleSpriteInit() {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	//TODO Seriously handle errors, asserts in this can be triggered by shader sources
	
	//Load Shader
	ShaderProgram = AR_LoadShaderProgram("./shader/SimpleSprite");

	//Setup Attributes
	Vao = AR_CreateVao();

	//-Vertex Positions
	//--Alocate buffer
	glGenBuffers(1, &VertexBuffer);
	//--Find //OPT Would be nice to use layout, or Bind before linking
	GLint vertPosAttribLoc;
	vertPosAttribLoc = glGetAttribLocation(ShaderProgram, "vertPos");
	assert(vertPosAttribLoc >= 0);
	//--Set
	AR_Vao_SetAttribute(Vao, VertexBuffer, vertPosAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, /*(GLvoid*)offsetof(AR_Vec2, x)*/ 0);

	//-Texture Coordinates
	glGenBuffers(1, &TextureCoordBuffer);
	//--Find
	GLint vertTexCoordAttribLoc;
	vertTexCoordAttribLoc = glGetAttribLocation(ShaderProgram, "vertTexCoord");
	assert(vertTexCoordAttribLoc >= 0);
	//--Set
	AR_Vao_SetAttribute(Vao, TextureCoordBuffer, vertTexCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Constant for SimpleSprite, so let's set the data up now
	TextureCoordData = (kmVec2*)malloc(sizeof(kmVec2)*4);
	kmVec2Fill(&(TextureCoordData[0]), 0.0f, 1.0f); //BL
	kmVec2Fill(&(TextureCoordData[1]), 1.0f, 1.0f); //BR
	kmVec2Fill(&(TextureCoordData[2]), 1.0f, 0.0f); //TR
	kmVec2Fill(&(TextureCoordData[3]), 0.0f, 0.0f); //TL
	
	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(kmVec2)*4, TextureCoordData, GL_STATIC_DRAW);
}

AR_SimpleSprite* AR_CreateSimpleSprite() {
	AR_SimpleSprite* this;
	this = (AR_SimpleSprite*)malloc(sizeof(AR_SimpleSprite));

	kmVec2Fill(&(this->position), -1.0f, -1.0f);
	kmVec2Fill(&(this->size), 2.0f, 2.0f);

	this->quad = AR_CreateQuad();

	AR_SimpleSprite_UpdateQuad(this);

	return this;
}

void AR_SimpleSprite_UpdateQuad(AR_SimpleSprite* this) {
	//Calculate quad from sprite data
	
	kmScalar left, bottom, right, top;
	left = this->position.x;
	bottom = this->position.y;
	right = left + this->size.x;
	top = bottom + this->size.y;
	
	kmVec2* quad;
	quad = this->quad;

	kmVec2Fill(&quad[0],  left, bottom); //BL
	kmVec2Fill(&quad[1], right, bottom); //BR
	kmVec2Fill(&quad[2], right,    top); //TR
	kmVec2Fill(&quad[3],  left,    top); //TL
}

void AR_SimpleSprite_Draw(AR_SimpleSprite* this) {
	glUseProgram(ShaderProgram); //TODO OPT Change to use shader object later?
	AR_Vao_Bind(Vao);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer); //TODO Maybe somehow allow this to be done in the Vao_Bind()
	glBufferData(GL_ARRAY_BUFFER, sizeof(kmVec2)*4, this->quad, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//OPT Need?, debug only?
	AR_Vao_Bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

