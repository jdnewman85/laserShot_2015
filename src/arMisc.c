#include "arMisc.h"

#include <stdio.h> //printf fprintf stderr NULL FILE SEEK*
#include <stdlib.h> //malloc free
#include <stdint.h> //uint*
#include <string.h> //str*

#include <GLES2/gl2.h> //gl* GL*
#include <kazmath/kazmath.h> //km* //OPT Already included with arMisc.h

void arPrintShaderLog(GLint shader) {
   // Prints the compile log for a shader
   char log[1024]; //BUG Check actual size
   glGetShaderInfoLog(shader, sizeof log, NULL, log);
   printf("%d:shader:\n%s\n", shader, log);
}


void arPrintProgramLog(GLint program) {
   // Prints the information log for a program object
   char log[1024]; //BUG Check actual size
   glGetProgramInfoLog(program, sizeof log, NULL, log);
   printf("%d:program:\n%s\n", program, log);
}

char* arLoadStringFromFile( char* filename ) {
	//Returns a string with the entire contents of file
	//Depends on stdio.h and stdlib.h
	FILE* inFile;
	int fileSize;
	char* tempString;

	/* TODO (james#5#): Add No filename format check? */
	inFile = fopen( filename, "r" );
	if( inFile == NULL ) {
		fprintf(stderr, "ERROR: Unable to open(read) file:'%s'\n", filename );
		return NULL;
	}
	if( fseek( inFile, 0, SEEK_END ) == -1 ) {
		fprintf(stderr, "ERROR: Unable to access(seek) file:'%s'\n", filename );
		fclose( inFile );
		return NULL;
	}
	fileSize = ftell( inFile );
	if( fileSize == -1 ) {
		fprintf(stderr, "ERROR: Unable to access(tell) file:'%s'\n", filename );
		fclose( inFile );
		return NULL;
	}
	if( fseek( inFile, 0, SEEK_SET ) == -1 ) {
		fprintf(stderr, "ERROR: Unable to access(seek) file:'%s'\n", filename );
		return NULL;
	}
	tempString = malloc( fileSize + 1 );
	if( tempString == NULL ) {
		fprintf(stderr, "ERROR: Unable to allocate memory for file:'%s'\n", filename );
		return NULL;
	}
	tempString[fileSize] = 0;
	if( fread( tempString, 1, fileSize, inFile ) != (uint32_t)(fileSize) ) {
		fprintf(stderr, "ERROR: Unable to read file:'%s'\n", filename );
		free( tempString );
		return NULL;
	}
	if( fclose( inFile ) != 0 ) {
		fprintf(stderr, "ERROR: Unable to close(read) file:'%s'\n", filename );
		return tempString;//???Already got our string
	}
	return tempString;
}

kmVec2* arCreateQuad() {
	kmVec2* this;

	this = (kmVec2*)malloc(sizeof(kmVec2)*4);
	//TODO Zero?

	return this;
}

GLuint arLoadShaderProgram(char* filename) {
	char tempFilename[1024];
	strcpy(tempFilename, filename);
	strcat(tempFilename, ".vert");
	GLchar* vertSource = arLoadStringFromFile(tempFilename);

	strcpy(tempFilename, filename);
	strcat(tempFilename, ".frag");
	GLchar* fragSource = arLoadStringFromFile(tempFilename);

	GLuint vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, (const GLchar**)&vertSource, 0);
	glCompileShader(vertShader);
	arAssertGl();

	arPrintShaderLog(vertShader);

	GLuint fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, (const GLchar**)&fragSource, 0);
	glCompileShader(fragShader);
	arAssertGl();

	arPrintShaderLog(fragShader);

	GLuint program;
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	arAssertGl();
	
	//Check for proper linking
	GLint isLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	arPrintProgramLog(program);
	assert(isLinked == GL_TRUE);
	arAssertGl();

	//Need this for glUniforms
	glUseProgram(program);

	return program;
}

