#include <assert.h>
#include <stdlib.h>
#include <stdint.h> //OPT already included/unneeded from stdlib.h

#include "../lib/lodepng.h"
#include "arImage.h"

arImage* arLoadImage(char* filename) {
	uint32_t error;
	uint32_t width, height;
	uint8_t* data;
	
	error = lodepng_decode32_file(&data, &width, &height, filename);
	assert(error == 0);

	//Good
	arImage* newImage;
	newImage = (arImage*)(malloc(sizeof(arImage)));
	
	newImage->width = width;
	newImage->height = height;
	newImage->data = data;

	return newImage;
}

void arImage_Destroy(arImage* image) {
	free(image->data);
	free(image);
}

