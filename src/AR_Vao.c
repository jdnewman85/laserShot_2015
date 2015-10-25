#include <stdlib.h>
#include <stdbool.h> //OPT Already in AR_Vao.h

#include <GLES2/gl2.h> //OPT Already in AR_Vao.h

#include "AR_Vao.h"

AR_Vao* AR_CreateVao() {
	//OPT Store vao->attributes pointer to prevent so many dereferences?
	AR_Vao* newVao;
	newVao = (AR_Vao*)malloc(sizeof(AR_Vao));

	for(int i = 0; i < GL_MAX_VERTEX_ATTRIBS; i++) {
		newVao->attributes[i].enabled = false;
		newVao->attributes[i].index = -1; //To cause an error if not set
		newVao->attributes[i].bufferId = 0;
		newVao->attributes[i].size = 4;
		newVao->attributes[i].type = GL_FLOAT;
		newVao->attributes[i].stride = 0;
		newVao->attributes[i].pointer = NULL;
	}

	return newVao;
}

void AR_Vao_Bind(AR_Vao* vao) {
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

