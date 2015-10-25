#include <stdio.h>

#include <GLES2/gl2.h>

#include "../include/Misc.h"


//Simple Opengl stuffs
//#define checkGL() = assert(glGetError() == 0)

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

