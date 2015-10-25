#include <stdio.h>
#include <stdlib.h>

#include <GLES2/gl2.h>

#include "AR_Misc.h"


//Simple Opengl stuffs
//#define AR_CheckGL() = assert(glGetError() == 0)

void AR_PrintShaderLog(GLint shader) {
   // Prints the compile log for a shader
   char log[1024]; //BUG Check actual size
   glGetShaderInfoLog(shader, sizeof log, NULL, log);
   printf("%d:shader:\n%s\n", shader, log);
}


void AR_PrintProgramLog(GLint program) {
   // Prints the information log for a program object
   char log[1024]; //BUG Check actual size
   glGetProgramInfoLog(program, sizeof log, NULL, log);
   printf("%d:program:\n%s\n", program, log);
}

char* AR_LoadStringFromFile( char* filename ) {
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

