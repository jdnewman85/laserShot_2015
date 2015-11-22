#ifndef __AR_SIMPLESPRITE_H__
#define __AR_SIMPLESPRITE_H__

#include <GLES2/gl2.h>

#include "AR_Math.h"

typedef struct {
	AR_Vec2	position;
	AR_Vec2	size;
	AR_Vec2	scale;
	AR_Vec4	color;
	AR_Float32 rotation;
	AR_Quad* quad;
} AR_SimpleSprite;

void AR_SimpleSpriteInit();
AR_SimpleSprite* AR_CreateSimpleSprite();
void AR_SimpleSprite_Draw(AR_SimpleSprite* this);

#endif //__AR_SIMPLESPRITE_H__

