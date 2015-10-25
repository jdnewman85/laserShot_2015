#include <stdlib.h>

#include <GLES2/gl2.h> //OPT Already in Texture.h

#include "../lib/lodepng.h"

#include "Image.h"
#include "Texture.h"

AR_Texture* AR_LoadTexture(char* filename) {
	AR_Image* tempImage;
	tempImage = AR_LoadImage(filename);

	GLuint textureId;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage->width, tempImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage->data);
	glGenerateMipmap(GL_TEXTURE_2D); //OPT Make Optional

	AR_Texture* newTexture;
	newTexture = (AR_Texture*)(malloc(sizeof(AR_Texture)));

	newTexture->width = tempImage->width;
	newTexture->height = tempImage->height;
	newTexture->textureId = textureId;

	AR_Image_Destroy(tempImage);

	return newTexture;
}

void AR_Texture_Destroy(AR_Texture* texture) {
	glDeleteTextures(1, &texture->textureId);

	free(texture);
}

