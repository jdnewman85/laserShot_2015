#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "Misc.h" //OPT In Debug.h
#include "Debug.h"

void AR_DebugInit(StateGL_t *state) {
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

	AR_PrintShaderLog(vshader);

	GLuint fshader;
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fshader_source, 0);
	glCompileShader(fshader);
	checkGL();

	AR_PrintShaderLog(fshader);

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

	AR_PrintProgramLog(program);
	
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

void AR_DebugDraw(StateGL_t *state) {
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

