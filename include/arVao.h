#ifndef __arVAO_H__
#define __arVAO_H__

#include <stdbool.h>

#include <GLES2/gl2.h>

#include "arMisc.h"

typedef struct {
	bool enabled;
	GLuint bufferId;
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid* pointer;
} arVertexAttribute;

typedef struct {
	arVertexAttribute attributes[AR_MAX_VERTEX_ATTRIBS];
} arVao;


arVao* arCreateVao();
void arVao_SetAttribute(arVao* vao, GLuint bufferId, GLuint index, GLint size,
		GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);
void arVao_Bind(arVao* vao);

#endif //__arVAO_H__

