
//Still need to have textures and uniforms bound with a drawable
//Note, not all uniforms need to be updated every object



#include "../include/argon.h"



#include <stdio.h> //printf

#include <kazmath/kazmath.h> //km*



static arGlState _state, *state=&_state;

int main() {
	printf("initGL\n");

	//TODO Maybe arGraphics returns the state?
	arGraphics(state); //TODO Add the inits to arGraphics
	arSimpleSpriteInit(state);
	arAssertGl();

	//Test load a png
	arTexture* myTexture;
	myTexture = arLoadTexture("./img/test.png");
	arAssertGl();

	//Make Some Sprites
	arSimpleSprite* sprite1;
	sprite1 = arCreateSimpleSprite(myTexture);
	kmVec2Fill(&(sprite1->position), 100.0f, 100.0f);
	arSimpleSprite_UpdateModel(sprite1);

	arSimpleSprite* sprite2;
	sprite2 = arCreateSimpleSprite(myTexture);
	kmVec2Fill(&(sprite2->position), state->displayWidth/2 - 250, state->displayHeight/2 - 250);
	arSimpleSprite_UpdateModel(sprite2);

	for(;;) {
		arCls();
		arAssertGl();

		arSimpleSprite_Draw(sprite1);
		arSimpleSprite_Draw(sprite2);
		arAssertGl();

		arFlip(state);
	}
       

	printf("End\n");

	return 0;
}

