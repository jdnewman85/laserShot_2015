#ifndef __arSIMPLESPRITE_H__
#define __arSIMPLESPRITE_H__

#include <kazmath/kazmath.h> //km*

#include "arGraphics.h" //arGlState
#include "arTexture.h" //arTexture

typedef struct {
	kmVec2	position;
//	kmVec2 offset;
//	kmVec2	size;
//	kmVec2	scale;
//	kmVec2	color;
//	kmScalar rotation;
	kmVec2* model;
	arTexture* texture;
} arSimpleSprite;

void arSimpleSpriteInit(arGlState* state);
arSimpleSprite* arCreateSimpleSprite(arTexture* texture);
void arSimpleSprite_UpdateModel(arSimpleSprite* this);
void arSimpleSprite_Draw(arSimpleSprite* this);

#endif //__arSIMPLESPRITE_H__

