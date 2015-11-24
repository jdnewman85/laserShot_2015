#include <stdlib.h>
#include <stdbool.h> //OPT Already in arVao.h

#include <GLES2/gl2.h> //OPT Already in arVao.h

#include "arVao.h"

//TODO Kind of need a better way to bind buffer, and update data

arVao* arCreateVao() {
	//OPT Store vao->attributes pointer to prevent so many dereferences?
	arVao* newVao;
	newVao = (arVao*)malloc(sizeof(arVao));

	for(int i = 0; i < GL_MAX_VERTEX_ATTRIBS; i++) {
		newVao->attributes[i].enabled = false;
		newVao->attributes[i].bufferId = -1; //To cause an error if not set //BUG TODO Doesn't actually cause an error
		newVao->attributes[i].index = -1; //To cause an error if not set //BUG Unsure if this actually causes an error
		newVao->attributes[i].size = 4;
		newVao->attributes[i].type = GL_FLOAT;
		newVao->attributes[i].normalized = GL_FALSE;
		newVao->attributes[i].stride = 0;
		newVao->attributes[i].pointer = NULL;
	}

	return newVao;
}

void arVao_SetAttribute(arVao* vao, GLuint bufferId, GLuint index, GLint size,
		GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer) {
	//NOTE OPT Defaults in CreateVao aren't really possible (always get set here)
	//OPT Store vao->attributes pointer to prevent so many dereferences?
	
	vao->attributes[index].enabled = true;
	vao->attributes[index].bufferId = bufferId;
	vao->attributes[index].index = index;
	vao->attributes[index].size = size;
	vao->attributes[index].type = type;
	vao->attributes[index].normalized = normalized;
	vao->attributes[index].stride = stride;
	vao->attributes[index].pointer = pointer;
}

void arVao_Bind(arVao* vao) {
	//OPT Store vao->attributes pointer to prevent so many dereferences?
	if(vao == NULL) {
		for(int i = 0; i < GL_MAX_VERTEX_ATTRIBS; i++) {
			glDisableVertexAttribArray(i);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0); //OPT Needed?
	} else {
		for(int i = 0; i < GL_MAX_VERTEX_ATTRIBS; i++) {
			if(vao->attributes[i].enabled) {
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, vao->attributes[i].bufferId);
				glVertexAttribPointer(vao->attributes[i].index, vao->attributes[i].size,
						vao->attributes[i].type, vao->attributes[i].normalized,
						vao->attributes[i].stride, vao->attributes[i].pointer);
			} else {
				glDisableVertexAttribArray(i);
			}
		}
	}
}

