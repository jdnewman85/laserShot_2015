#ifndef __arMISC_H__
#define __arMISC_H__

#include <assert.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "arImage.h"
#include "arTexture.h"

typedef struct {
	uint32_t displayWidth, displayHeight;

	// OpenGL|ES objects
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	
	kmMat4 projectionMatrix;
} arGlState;

#define arAssertGl() assert(glGetError() == 0);

void arPrintShaderLog(GLint shader);
void arPrintProgramLog(GLint shader);
char* arLoadStringFromFile(char* filename);

kmVec2* arCreateQuad();

GLuint arLoadShaderProgram(char* filename);

#endif //__arMISC_H__

