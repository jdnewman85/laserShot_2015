#include <assert.h>
#include <stdio.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <bcm_host.h>
#include <kazmath/kazmath.h> //Opt in Grpahics.h

#include "arMisc.h" //Opt in Graphics.h

#define GLES_VERSION 2

EGL_DISPMANX_WINDOW_T nativewindow; //IMPORTANT! Must be static or global

kmMat4 arProjectionMatrix;

void arGraphics(arGlState *state) {
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
	arAssertGl();
	
	//Init EGL Display
	result = eglInitialize(state->display, NULL, NULL);
	assert(EGL_FALSE != result);
	arAssertGl();
	
	//Choose Config //NOTE: Just chooses first match
	result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
	assert(EGL_FALSE != result);
	arAssertGl();
	
	//Bind API
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);
	arAssertGl();
	
	//Create Rendering Context
	EGLContext context;
	context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);
	assert(context!=EGL_NO_CONTEXT);
	arAssertGl();
	
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
	arAssertGl();
	
	state->surface = eglCreateWindowSurface(state->display, config, &nativewindow, NULL);
	assert(state->surface != EGL_NO_SURFACE);
	arAssertGl();
	
	//Connect context and surface
	result = eglMakeCurrent(state->display, state->surface, state->surface, context);
	assert(EGL_FALSE != result);
	arAssertGl();

	// Set background color and clear buffers
	glClearColor(0.00f, 0.00f, 0.95f, 1.0f); //OPT Remove?
	glClear(GL_COLOR_BUFFER_BIT);
	arAssertGl();

	// Prepare viewport
	glViewport (0, 0, state->screen_width, state->screen_height);
	arAssertGl();

	// Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	arAssertGl();

	//Setup Projection Matrix
	kmMat4OrthographicProjection(&arProjectionMatrix, 0.0f, state->screen_width, 0.0f, state->screen_height, -1.0f, 1.0f);

	state->context = context; //OPT REmove state->context?
}

void arCls() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void arFlip(arGlState *state) {
        eglSwapBuffers(state->display, state->surface);
}

