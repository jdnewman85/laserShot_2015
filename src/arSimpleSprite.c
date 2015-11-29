#include <assert.h>
#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in arSimpleSprite.h

#include "arVao.h"
#include "arMisc.h"
#include "arSimpleSprite.h"
#include "arGraphics.h"

//OPT COULD MAYBE MAKE THIS WHOLE THING INTO A CLASS IT'S OWN
//USE MAP FOR ATTRIBUTES?

static GLuint ShaderProgram;
static arVao* Vao;
static GLuint VertexBuffer; //OPT Better variable names?
static GLuint TextureCoordBuffer;

static kmVec2* TextureCoordData; //TODO Do these really need to be global? Also, maybe Stack?

void arSimpleSpriteInit(arGlState* state) {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	//TODO Seriously handle errors, asserts in this can be triggered by shader sources
	
	//Load Shader
	ShaderProgram = arLoadShaderProgram("./shader/SimpleSprite");

	//Setup Attributes
	Vao = arCreateVao();

	//-Vertex Positions
	//--Alocate buffer
	glGenBuffers(1, &VertexBuffer);
	//--Find //OPT Would be nice to use layout, or Bind before linking
	GLint vertPosAttribLoc;
	vertPosAttribLoc = glGetAttribLocation(ShaderProgram, "vertPos");
	assert(vertPosAttribLoc != -1);
	//--Set
	arVao_SetAttribute(Vao, VertexBuffer, vertPosAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, /*(GLvoid*)offsetof(arVec2, x)*/ 0);

	//-Texture Coordinates
	glGenBuffers(1, &TextureCoordBuffer);
	//--Find
	GLint vertTexCoordAttribLoc;
	vertTexCoordAttribLoc = glGetAttribLocation(ShaderProgram, "vertTexCoord");
	assert(vertTexCoordAttribLoc != -1);
	//--Set
	arVao_SetAttribute(Vao, TextureCoordBuffer, vertTexCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Constant for SimpleSprite, so let's set the data up now
	TextureCoordData = (kmVec2*)malloc(sizeof(kmVec2)*4);
	kmVec2Fill(&(TextureCoordData[0]), 0.0f, 1.0f); //BL
	kmVec2Fill(&(TextureCoordData[1]), 1.0f, 1.0f); //BR
	kmVec2Fill(&(TextureCoordData[2]), 1.0f, 0.0f); //TR
	kmVec2Fill(&(TextureCoordData[3]), 0.0f, 0.0f); //TL
	
	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(kmVec2)*4, TextureCoordData, GL_STATIC_DRAW);

	//Orthogonal Projection
	GLint projectionMatrixLoc;
	projectionMatrixLoc = glGetUniformLocation(ShaderProgram, "projectionMatrix");
	assert(projectionMatrixLoc != -1);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, (GLfloat*)&(state->projectionMatrix));
}

arSimpleSprite* arCreateSimpleSprite() {
	arSimpleSprite* this;
	this = (arSimpleSprite*)malloc(sizeof(arSimpleSprite));

	kmVec2Fill(&(this->position), -1.0f, -1.0f);
	kmVec2Fill(&(this->size), 2.0f, 2.0f);

	this->model = arCreateQuad();

	arSimpleSprite_UpdateModel(this);

	return this;
}

void arSimpleSprite_UpdateModel(arSimpleSprite* this) {
	//Calculate quad from sprite data
	
	kmScalar left, bottom, right, top;
	left = this->position.x;
	bottom = this->position.y;
	right = left + this->size.x;
	top = bottom + this->size.y;
	
	kmVec2* model;
	model = this->model;

	kmVec2Fill(&model[0],  left, bottom); //BL
	kmVec2Fill(&model[1], right, bottom); //BR
	kmVec2Fill(&model[2], right,    top); //TR
	kmVec2Fill(&model[3],  left,    top); //TL

	//IDEA OPT TODO May move the transform stuffs to it's own class...
	//TODO OPT Need to store either the transformation matrix, or the final quad and only update if dirty
	//ALRIGHT, need to do some matrix mathy transformationy stuffsy
	//Order of transformations:
	//Position/Size
	//Offset
	//Rotation
	//Scale
	
}

void arSimpleSprite_Draw(arSimpleSprite* this) {
	glUseProgram(ShaderProgram); //TODO OPT Change to use shader object later?
	arVao_Bind(Vao);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer); //TODO Maybe somehow allow this to be done in the Vao_Bind()
	glBufferData(GL_ARRAY_BUFFER, sizeof(kmVec2)*4, this->model, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//OPT Need?, debug only?
	arVao_Bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

