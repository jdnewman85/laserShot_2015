#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdint.h>

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	uint8_t* data;
} AR_Image;


AR_Image* AR_LoadImage(char* filename);
void AR_Image_Destroy(AR_Image* image);

#endif //__IMAGE_H__
