#ifndef __AR_MISC_H__
#define __AR_MISC_H__

#include <assert.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <kazmath/kazmath.h>

#include "AR_Image.h"
#include "AR_Texture.h"

typedef struct {
	uint32_t screen_width;
	uint32_t screen_height;

	// OpenGL|ES objects
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	
	GLuint program;
	GLuint vertexBuffer;
} StateGL_t;

#define AR_CheckGL() assert(glGetError() == 0);

void AR_PrintShaderLog(GLint shader);
void AR_PrintProgramLog(GLint shader);
char* AR_LoadStringFromFile(char* filename);

kmVec2* AR_CreateQuad();

#endif //__AR_MISC_H__

