#include <assert.h>
#include <stdlib.h>
#include <stdint.h> //OPT already included/unneeded from stdlib.h

#include "../lib/lodepng.h"
#include "Image.h"

AR_Image* AR_LoadImage(char* filename) {
	uint32_t error;
	uint32_t width, height;
	uint8_t* data;
	
	error = lodepng_decode32_file(&data, &width, &height, filename);
	assert(error == 0);

	//Good
	AR_Image* newImage;
	newImage = (AR_Image*)(malloc(sizeof(AR_Image)));
	
	newImage->width = width;
	newImage->height = height;
	newImage->data = data;

	return newImage;
}

void AR_Image_Destroy(AR_Image* image) {
	free(image->data);
	free(image);
}

