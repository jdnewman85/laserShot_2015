#ifndef __arGRAPHICS_H__
#define __arGRAPHICS_H__

#include <stdint.h> //uint*

#include <EGL/egl.h> //EGL*
#include <kazmath/kazmath.h> //km*

typedef struct {
	uint32_t displayWidth, displayHeight;

	// OpenGL|ES objects
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	
	kmMat4 projectionMatrix;
} arGlState;

void arGraphics(arGlState *state);
void arCls();
void arFlip(arGlState *state);

#endif //__arGRAPHICS_H__

