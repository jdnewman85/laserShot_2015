#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in Sprite.h

#include "AR_Vao.h"
#include "AR_Debug.h"
#include "AR_Sprite.h"

static GLuint ShaderProgram;
static AR_Vao* Vao;

void AR_SpriteInit() {
	//TODO Return errors (Since files could be missing, and assert won't be in release build)
	
	//Load Shader
//	ShaderProgram = AR_LoadShaderProgram("./shader/sprite");

	//Find Attributes //OPT Would be nice to use layout, or Bind before linking
	GLuint positionAttribLoc, sizeAttribLoc, scaleAttribLoc, angleAttribLoc, colorAttribLoc;
	positionAttribLoc = glGetAttribLocation(ShaderProgram, "vertPosition");
	sizeAttribLoc = glGetAttribLocation(ShaderProgram, "vertSize");
	scaleAttribLoc = glGetAttribLocation(ShaderProgram, "vertScale");
	angleAttribLoc = glGetAttribLocation(ShaderProgram, "vertAngle");
	colorAttribLoc = glGetAttribLocation(ShaderProgram, "vertColor");
	
	//Setup Attributes
	Vao = AR_CreateVao();
	AR_Vao_SetAttribute(Vao, positionAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(AR_Sprite), (GLvoid*)offsetof(AR_Sprite, x));
	AR_Vao_SetAttribute(Vao, sizeAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(AR_Sprite), (GLvoid*)offsetof(AR_Sprite, width));
	AR_Vao_SetAttribute(Vao, scaleAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(AR_Sprite), (GLvoid*)offsetof(AR_Sprite, scaleX));
	AR_Vao_SetAttribute(Vao, angleAttribLoc, 1, GL_FLOAT, GL_FALSE, sizeof(AR_Sprite), (GLvoid*)offsetof(AR_Sprite, angle));
	AR_Vao_SetAttribute(Vao, colorAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(AR_Sprite), (GLvoid*)offsetof(AR_Sprite, red));
}

AR_Sprite* AR_CreateSprite() {
	AR_Sprite* newSprite;
	newSprite = (AR_Sprite*)malloc(sizeof(AR_Sprite));

	newSprite->x = 0.0f;
	newSprite->y = 0.0f;
	newSprite->width = 0.0f;
	newSprite->height = 0.0f;
	newSprite->scaleX = 1.0f;
	newSprite->scaleY = 1.0f;
	newSprite->angle = 0.0f;
	newSprite->red = 1.0f;
	newSprite->green = 1.0f;
	newSprite->blue = 1.0f;
	newSprite->alpha = 1.0f;

	return newSprite;
}

