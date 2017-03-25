#include "PowerPellet.h"

#include <stdio.h>

void PowerPellet::draw(){
	if(sprite.sprite == pellet) sprite.sprite = pelletbig;
	else sprite.sprite = pellet;
	printf("DRAW\r\n");
}
