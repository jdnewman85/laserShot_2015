package main

/*
	#cgo CFLAGS: -I.
	#cgo LDFLAGS: -L../ -lpiGL
	#include "../include/openGLMisc.h"
*/
import "C"

import "fmt"

func main() {
	fmt.Println("FUCKS YEAH!")

	var myState C.StateGL_t

	myStatePtr := &myState

	C.initGL(myStatePtr)
	C.debugSetupGL(myStatePtr)

	for {
	}
}
