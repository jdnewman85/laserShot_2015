#include <stdlib.h>

#include "AR_Math.h"

void AR_Vec2_Set(AR_Vec2* this, AR_Float32 x, AR_Float32 y) {
	this->x = x;
	this->y = y;
}

void AR_Vec3_Set(AR_Vec3* this, AR_Float32 x, AR_Float32 y, AR_Float32 z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void AR_Vec4_Set(AR_Vec4* this, AR_Float32 x, AR_Float32 y, AR_Float32 z, AR_Float32 w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

AR_Vec2* AR_CreateQuad() {
	AR_Vec2* this;

	this = (AR_Vec2*)malloc(sizeof(AR_Vec2)*4);
	//TODO Zero?

	return this;
}

