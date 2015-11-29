#ifndef __arSIMPLESPRITE_H__
#define __arSIMPLESPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	kmVec2	position;
//	kmVec2 offset;
	kmVec2	size;
//	kmVec2	scale;
//	kmVec2	color;
//	kmScalar rotation;
	kmVec2* model;
} arSimpleSprite;

void arSimpleSpriteInit(arGlState* state);
arSimpleSprite* arCreateSimpleSprite();
void arSimpleSprite_UpdateModel(arSimpleSprite* this);
void arSimpleSprite_Draw(arSimpleSprite* this);

#endif //__arSIMPLESPRITE_H__

