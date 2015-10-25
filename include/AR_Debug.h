#ifndef __AR_DEBUG_H__
#define __AR_DEBUG_H__

#include <GLES2/gl2.h>

#include "AR_Misc.h"

GLuint AR_LoadShaderProgram(char* filename);
void AR_DebugInit(StateGL_t *state);
void AR_DebugDraw(StateGL_t *state);

#endif //__AR_DEBUG_H__

