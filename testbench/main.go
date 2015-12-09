package main

/*
#cgo LDFLAGS: -lkazmath
#include "../include/argon.h"
*/
import "C"

import (
	"fmt"
)

var(
	_state C.arGlState
	state *C.arGlState = &_state
)

func main() {
	fmt.Println("test")
	C.PrintSomeNum(4)

	C.arGraphics(state)
	C.arSimpleSpriteInit(state)

	//Test load a png
	myTexture := C.arLoadTexture(C.CString("./img/test.png"));

	//Make Some Sprites
	sprite1 := C.arCreateSimpleSprite(myTexture);
	C.kmVec2Fill(&(sprite1.position), 100.0, 100.0);
	C.arSimpleSprite_UpdateModel(sprite1);

	sprite2 := C.arCreateSimpleSprite(myTexture);
	C.kmVec2Fill(&(sprite2.position), C.float(state.displayWidth/2 - 250), C.float(state.displayHeight/2 - 250));
	C.arSimpleSprite_UpdateModel(sprite2);

	for {
		C.arCls();

		C.arSimpleSprite_Draw(sprite1);
		C.arSimpleSprite_Draw(sprite2);

		C.arFlip(state);
	}

	fmt.Println("Quit")
}
