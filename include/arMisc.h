#ifndef __arMISC_H__
#define __arMISC_H__

#include <assert.h> //assert (in macro)

#include <GLES2/gl2.h> //GL*
#include <kazmath/kazmath.h> //km*

#define AR_MAX_VERTEX_ATTRIBS 8 //TODO Add an asser check for this =< glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n) at runtime
#define arAssertGl() assert(glGetError() == 0);

void PrintSomeNum(int someNum);
void arPrintShaderLog(GLint shader);
void arPrintProgramLog(GLint shader);
char* arLoadStringFromFile(char* filename);

kmVec2* arCreateQuad();

GLuint arLoadShaderProgram(char* filename);

#endif //__arMISC_H__

