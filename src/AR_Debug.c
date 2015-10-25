#include <string.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "AR_Misc.h" //OPT In Debug.h
#include "AR_Debug.h"

GLuint AR_LoadShaderProgram(char* filename) {
	//TODO BUG TEMP
	//Need to actually load from file
	const GLchar* vertSourceOLD =
		"attribute vec4 vertex;"
		"attribute vec2 vertTexCoord;"
		"varying vec2 fragTexCoord;"
		""
		"void main(void) {"
		"	fragTexCoord = vertTexCoord;"
		""
		"	gl_Position = vertex;"
		"}";

	const GLchar* fragSourceOLD =
		"varying lowp vec2 fragTexCoord;"
		"uniform sampler2D Texture;"
		""
		"void main(void) {"
		"	gl_FragColor = texture2D(Texture, fragTexCoord);"
		"}";

	char tempFilename[1024];
	strcpy(tempFilename, filename);
	strcat(tempFilename, ".vert");
	GLchar* vertSource = AR_LoadStringFromFile(tempFilename);

	strcpy(tempFilename, filename);
	strcat(tempFilename, ".frag");
	GLchar* fragSource = AR_LoadStringFromFile(tempFilename);

	GLuint vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, (const GLchar**)&vertSource, 0);
	glCompileShader(vertShader);
	AR_CheckGL();

	AR_PrintShaderLog(vertShader);

	GLuint fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, (const GLchar**)&fragSource, 0);
	glCompileShader(fragShader);
	AR_CheckGL();

	AR_PrintShaderLog(fragShader);

	GLuint program;
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	AR_CheckGL();
	
	//Check for proper linking
	GLint isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	AR_PrintProgramLog(program);
	assert(isLinked == GL_TRUE);
	AR_CheckGL();

	return program;
}

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

	GLuint program;
	program = AR_LoadShaderProgram("./shader/sprite");
	
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
	AR_CheckGL();

	//Texture Coord data
	GLuint texCoordBuffer;
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_texCoords), vertex_texCoords, GL_STATIC_DRAW);

	GLuint texCoordLoc;
	texCoordLoc = glGetAttribLocation(program, "vertTexCoord");
	glEnableVertexAttribArray(texCoordLoc);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	AR_CheckGL();

        glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(program);
	AR_CheckGL();

	//TODO OPT
	//For now, we're just going to use 1 sampler/texture unit
	GLint texLoc;
	texLoc = glGetUniformLocation(program, "Texture");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texLoc, 0);
	AR_CheckGL();
	
	//Save state OPT BUG TODO
	state->program = program;
	state->vertexBuffer = vertexBuffer;
}

void AR_DebugDraw(StateGL_t *state) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); //Certainly probalby not needed every frame OPT

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        AR_CheckGL();
        
        glBindBuffer(GL_ARRAY_BUFFER, state->vertexBuffer); //OPT Only needed to call glBufferData to change stuffs...
        AR_CheckGL();

        glUseProgram(state->program); //Only needed when switching programs OPT
        AR_CheckGL();
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        AR_CheckGL();

        glBindBuffer(GL_ARRAY_BUFFER, 0); //Good to catch accidental buffer use, but OPT

        glFlush();
        glFinish();
        AR_CheckGL();
        
        eglSwapBuffers(state->display, state->surface);
        AR_CheckGL();
}

