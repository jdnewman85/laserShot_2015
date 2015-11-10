#ifndef __AR_POINTSPRITE_H__
#define __AR_POINTSPRITE_H__

#include <GLES2/gl2.h>

typedef struct {
	GLfloat	x, y;
} AR_PointSprite;


void AR_PointSpriteInit();
AR_PointSprite* AR_CreatePointSprites(int count);
void AR_PointSprite_Draw(AR_PointSprite* simpleSprite, int count);

#endif //__AR_POINTSPRITE_H__

