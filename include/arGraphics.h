#ifndef __arGRAPHICS_H__
#define __arGRAPHICS_H__

#include <kazmath/kazmath.h>

#include "arMisc.h"

extern kmMat4 arProjectionMatrix; //TODO Add to the state

void arGraphics(arGlState *state);
void arCls();
void arFlip(arGlState *state);

#endif //__arGRAPHICS_H__

