#ifndef __AR_MATH_H__
#define __AR_MATH_H__

typedef float AR_Float32;

typedef struct {
	AR_Float32 x, y;
} AR_Vec2;

typedef struct {
	AR_Float32 x, y, z;
} AR_Vec3;

typedef struct {
	AR_Float32 x, y, z, w;
} AR_Vec4;

typedef struct {
	AR_Vec2 points[4];
} AR_Quad;

void AR_Vec2_Set(AR_Vec2* this, AR_Float32 x, AR_Float32 y);
void AR_Vec3_Set(AR_Vec3* this, AR_Float32 x, AR_Float32 y, AR_Float32 z);
void AR_Vec4_Set(AR_Vec4* this, AR_Float32 x, AR_Float32 y, AR_Float32 z, AR_Float32 w);
AR_Quad* AR_CreateQuad();

#endif //__AR_MATH_H__
