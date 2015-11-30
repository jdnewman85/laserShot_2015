#ifndef __arIMAGE_H__
#define __arIMAGE_H__

#include <stdint.h> //uint*

typedef struct {
	 //OPT 16bit width and height?
	uint32_t width, height;
	uint8_t* data;
} arImage;


arImage* arLoadImage(char* filename);
void arImage_Destroy(arImage* image);

#endif //__arIMAGE_H__

