#ifndef __arTEXTURE_H__
#define __arTEXTURE_H__

#include <stdint.h> //uint*

#include <GLES2/gl2.h> //GL*

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	GLuint textureId;
} arTexture;


arTexture* arLoadTexture(char* filename);
void arTexture_Destroy(arTexture* texture);

#endif //__arTEXTURE_H__

