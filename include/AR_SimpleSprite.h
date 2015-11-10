#ifndef __AR_SIMPLESPRITE_H__
#define __AR_SIMPLESPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	GLfloat	x, y;
} AR_SimpleSprite;


void AR_SimpleSpriteInit();
AR_SimpleSprite* AR_CreateSimpleSprites(int count);
void AR_SimpleSprite_Draw(AR_SimpleSprite* simpleSprite, int count);

#endif //__AR_SIMPLESPRITE_H__

