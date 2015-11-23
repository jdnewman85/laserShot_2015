#ifndef __AR_SIMPLESPRITE_H__
#define __AR_SIMPLESPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	kmVec2	position;
//	kmVec2 offset;
	kmVec2	size;
//	kmVec2	scale;
//	kmVec2	color;
//	kmScalar rotation;
	kmVec2* quad;
} AR_SimpleSprite;

void AR_SimpleSpriteInit();
AR_SimpleSprite* AR_CreateSimpleSprite();
void AR_SimpleSprite_Draw(AR_SimpleSprite* this);

#endif //__AR_SIMPLESPRITE_H__

