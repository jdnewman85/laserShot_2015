#ifndef __AR_SPRITE_H__
#define __AR_SPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	GLfloat	x, y;
	GLfloat width, height;
	GLfloat scaleX, scaleY;
	GLfloat angle;
	GLfloat red, green, blue, alpha;
} AR_Sprite;


void AR_SpriteInit();
AR_Sprite* AR_CreateSprite();

#endif //__AR_SPRITE_H__

