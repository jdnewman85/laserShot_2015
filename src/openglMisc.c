#include <assert.h>
#include <stdio.h>

#include <bcm_host.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

#include "../lib/lodepng.h"
#include "../include/openglMisc.h"


//Simple Opengl stuffs
//#define checkGL() = assert(glGetError() == 0);


EGL_DISPMANX_WINDOW_T nativewindow; //IMPORTANT! Must be static or global

Image_t* loadImage(char* filename) {
	uint32_t error;
	uint32_t width, height;
	uint8_t* data;
	
	error = lodepng_decode32_file(&data, &width, &height, filename);
	assert(error == 0);

	//Good
	Image_t* newImage;
	newImage = (Image_t*)(malloc(sizeof(Image_t)));
	
	newImage->width = width;
	newImage->height = height;
	newImage->data = data;

	return newImage;
}

void freeImage(Image_t* image) {
	free(image->data);
	free(image);
}

TextureGL_t* loadTexture(char* filename) {
	Image_t* tempImage;
	tempImage = loadImage(filename);

	GLuint textureId;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage->width, tempImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage->data);
	glGenerateMipmap(GL_TEXTURE_2D); //OPT Make Optional
	checkGL();

	TextureGL_t* newTexture;
	newTexture = (TextureGL_t*)(malloc(sizeof(TextureGL_t)));

	newTexture->width = tempImage->width;
	newTexture->height = tempImage->height;
	newTexture->textureId = textureId;

	return newTexture;
}

void freeTextureGL(TextureGL_t* texture) {
	glDeleteTextures(1, &texture->textureId);

	free(texture);
}

void initGL(StateGL_t *state) {
//Arguments: CUBE_STATE_T *state - holds OGLES model info
//Description: Sets the display, OpenGL|ES context and screen stuff
//TODO Rewrite bits to have variables closer to use
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;
	
	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
	
	//Window Attributes
	const EGLint attribute_list[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};
	
	//Context Attributes
	const EGLint context_attributes[] = {
		EGL_CONTEXT_CLIENT_VERSION, GLES_VERSION,
		EGL_NONE
	};
	EGLConfig config;
	
	//Init Broadcom
	bcm_host_init();

	//Get EGL Display
	state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(state->display!=EGL_NO_DISPLAY);
	checkGL();
	
	//Init EGL Display
	result = eglInitialize(state->display, NULL, NULL);
	assert(EGL_FALSE != result);
	checkGL();
	
	//Choose Config //NOTE: Just chooses first match
	result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
	assert(EGL_FALSE != result);
	checkGL();
	
	//Bind API
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);
	checkGL();
	
	//Create Rendering Context
	EGLContext context;
	context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
	assert(context!=EGL_NO_CONTEXT);
	checkGL();
	
	//Setup Window Surface
	success = graphics_get_display_size(0 /* LCD */, &state->screen_width, &state->screen_height);
	assert( success >= 0 );
	//DEBUG
	fprintf(stderr, "Display Size: '%dx%d'\n", state->screen_width, state->screen_height);
	
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = state->screen_width;
	dst_rect.height = state->screen_height;
	   
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = state->screen_width << 16;
	src_rect.height = state->screen_height << 16;        
	
	dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
	dispman_update = vc_dispmanx_update_start(0);
	      
	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display,
		0/*layer*/, &dst_rect, 0/*src*/,
		&src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
	   
	nativewindow.element = dispman_element;
	nativewindow.width = state->screen_width;
	nativewindow.height = state->screen_height;
	vc_dispmanx_update_submit_sync(dispman_update);
	   
	checkGL();
	
	state->surface = eglCreateWindowSurface(state->display, config, &nativewindow, NULL);
	assert(state->surface != EGL_NO_SURFACE);
	checkGL();
	
	//Connect context and surface
	result = eglMakeCurrent(state->display, state->surface, state->surface, context);
	assert(EGL_FALSE != result);
	checkGL();
	
	// Set background color and clear buffers
	glClearColor(0.00f, 0.00f, 0.95f, 1.0f); //OPT Remove?
	glClear(GL_COLOR_BUFFER_BIT);
	checkGL();

	state->context = context; //OPT REmove state->context?
}

void clearGL() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void flipGL(StateGL_t *state) {
        eglSwapBuffers(state->display, state->surface);
}

void debugSetupGL(StateGL_t *state) {
	const GLfloat vertex_data[] = {
		-1.0,	-1.0,	 1.0,	 1.0,
		 1.0,	-1.0,	 1.0,	 1.0,
		 1.0,	 1.0,	 1.0,	 1.0,
		-1.0,	 1.0,	 1.0,	 1.0
   	}; //TODO MOVE
	const GLfloat vertex_texCoords[] = {
		  0.0,	  1.0,
		  1.0,	  1.0,
		  1.0,	  0.0,
		  0.0,	  0.0
	}; //TODO MOVE?
	const GLchar *vshader_source =
		"attribute vec4 vertex;"
		"attribute vec2 vertTexCoord;"
		"varying vec2 fragTexCoord;"
		""
		"void main(void) {"
		"	fragTexCoord = vertTexCoord;"
		""
		"	gl_Position = vertex;"
		"}";

	const GLchar *fshader_source =
		"varying lowp vec2 fragTexCoord;"
		"uniform sampler2D Texture;"
		""
		"void main(void) {"
		"	gl_FragColor = texture2D(Texture, fragTexCoord);"
		"}";

	GLuint vshader;
	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vshader_source, 0);
	glCompileShader(vshader);
	checkGL();

	showShaderLogGL(vshader);

	GLuint fshader;
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fshader_source, 0);
	glCompileShader(fshader);
	checkGL();

	showShaderLogGL(fshader);

	GLuint program;
	program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);
	
	//Check for proper linking
	GLint isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	assert(isLinked == GL_TRUE);
	checkGL();

	showProgramLogGL(program);
	
	glClearColor ( 0.7, 0.7, 0.7, 1.0 );
	
	//OPT BUG TODO NEEDED?
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkGL();

	// Prepare viewport
	glViewport (0, 0, state->screen_width, state->screen_height);
	checkGL();
	
	// Upload vertex data to a buffer
	// BUG OPT TODO REMOVE OR MOVE
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	GLuint vertexAttribLoc;
	vertexAttribLoc = glGetAttribLocation(program, "vertex");
	glEnableVertexAttribArray(vertexAttribLoc);
	glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	checkGL();

	//Texture Coord data
	GLuint texCoordBuffer;
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_texCoords), vertex_texCoords, GL_STATIC_DRAW);

	GLuint texCoordLoc;
	texCoordLoc = glGetAttribLocation(program, "vertTexCoord");
	glEnableVertexAttribArray(texCoordLoc);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	checkGL();

        glBindBuffer(GL_ARRAY_BUFFER, 0); //OPT NEEDED?

	glUseProgram(program);
	checkGL();

	//Save state OPT BUG TODO
	state->program = program;
	state->vertexBuffer = vertexBuffer;
}

void drawScreenQuadGL(StateGL_t *state) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); //Certainly probalby not needed every frame OPT

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        checkGL();
        
        glBindBuffer(GL_ARRAY_BUFFER, state->vertexBuffer); //OPT Only needed to call glBufferData to change stuffs...
        checkGL();

        glUseProgram(state->program); //Only needed when switching programs OPT
        checkGL();
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        checkGL();

        glBindBuffer(GL_ARRAY_BUFFER, 0); //Good to catch accidental buffer use, but OPT

        glFlush();
        glFinish();
        checkGL();
        
        eglSwapBuffers(state->display, state->surface);
        checkGL();
}

void showShaderLogGL(GLint shader) {
   // Prints the compile log for a shader
   char log[1024]; //BUG Check actual size
   glGetShaderInfoLog(shader, sizeof log, NULL, log);
   printf("%d:shader:\n%s\n", shader, log);
}


void showProgramLogGL(GLint program) {
   // Prints the information log for a program object
   char log[1024]; //BUG Check actual size
   glGetProgramInfoLog(program, sizeof log, NULL, log);
   printf("%d:program:\n%s\n", program, log);
}

