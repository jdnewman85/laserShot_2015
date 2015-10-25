#ifndef __MISC_H__
#define __MISC_H__

#include <assert.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "Image.h"
#include "Texture.h"

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

//Simple Opengl stuffs

#define checkGL() assert(glGetError() == 0);

void AR_PrintShaderLog(GLint shader);
void AR_PrintProgramLog(GLint shader);

#endif //__MISC_H__
