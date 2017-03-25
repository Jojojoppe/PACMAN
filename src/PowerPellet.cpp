#include "PowerPellet.h"

void PowerPellet::draw(){
	if(sprite.sprite == pellet) sprite.sprite = pelletbig;
	else sprite.sprite = pellet;
}
