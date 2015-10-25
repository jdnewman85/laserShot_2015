#ifndef __AR_VAO_H__
#define __AR_VAO_H__

#include <stdbool.h>

#include <GLES2/gl2.h>

typedef struct {
	bool enabled;
	int index;
	GLuint bufferId;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid* pointer;
} AR_VertexAttribute;

typedef struct {
	AR_VertexAttribute attributes[GL_MAX_VERTEX_ATTRIBS];
} AR_Vao;


AR_Vao* AR_CreateVao();
void AR_Vao_Bind(AR_Vao* vao);

#endif //__AR_VAO_H__

