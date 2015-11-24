#ifndef __arMISC_H__
#define __arMISC_H__

#include <assert.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "arImage.h"
#include "arTexture.h"

typedef struct {
	uint32_t screen_width;
	uint32_t screen_height;

	// OpenGL|ES objects
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	
	GLuint program;
	GLuint vertexBuffer;
} arGlState;

#define arAssertGl() assert(glGetError() == 0);

void arPrintShaderLog(GLint shader);
void arPrintProgramLog(GLint shader);
char* arLoadStringFromFile(char* filename);

kmVec2* arCreateQuad();

GLuint arLoadShaderProgram(char* filename);

#endif //__arMISC_H__

