#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in Texture.h

#include "../lib/lodepng.h"

#include "arImage.h"
#include "arTexture.h"

arTexture* arLoadTexture(char* filename) {
	arImage* tempImage;
	tempImage = arLoadImage(filename);

	GLuint textureId;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage->width, tempImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage->data);
	glGenerateMipmap(GL_TEXTURE_2D); //OPT Make Optional

	arTexture* newTexture;
	newTexture = (arTexture*)(malloc(sizeof(arTexture)));

	newTexture->width = tempImage->width;
	newTexture->height = tempImage->height;
	newTexture->textureId = textureId;

	arImage_Destroy(tempImage);

	return newTexture;
}

void arTexture_Destroy(arTexture* texture) {
	glDeleteTextures(1, &texture->textureId);

	free(texture);
}

