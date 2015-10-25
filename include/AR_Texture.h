#ifndef __AR_TEXTURE_H__
#define __AR_TEXTURE_H__

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	GLuint textureId;
} AR_Texture;


AR_Texture* AR_LoadTexture(char* filename);
void AR_Texture_Destroy(AR_Texture* texture);

#endif //__AR_TEXTURE_H__

