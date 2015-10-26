#ifndef __AR_SIMPLESPRITE_H__
#define __AR_SIMPLESPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	GLfloat	x, y;
} AR_SimpleSprite;


void AR_SimpleSpriteInit();
AR_SimpleSprite* AR_CreateSimpleSprite();

#endif //__AR_SIMPLESPRITE_H__

