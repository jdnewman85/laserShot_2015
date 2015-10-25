#ifndef __OPENGLMISC_H__
#define __OPENGLMISC_H__

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#define GLES_VERSION 2

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

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	uint8_t* data;
} Image_t;

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	GLuint textureId;
} TextureGL_t;

//Simple Opengl stuffs

#define checkGL() assert(glGetError() == 0);

void initGL(StateGL_t *state);
void clearGL();
void flipGL(StateGL_t *state);

void debugSetupGL(StateGL_t *state);
void drawScreenQuadGL(StateGL_t *state);

void showShaderLogGL(GLint shader);
void showProgramLogGL(GLint shader);

Image_t* loadImage(char* filename);
void freeImage(Image_t* image);
TextureGL_t* loadTexture(char* filename);
void freeTextureGL(TextureGL_t* texture);
#endif //__OPENGLMISC_H__
