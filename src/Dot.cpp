#include "Dot.h"
#include <Game.h>

void Dot::eat(void * game){
	if(!eaten){
		sprite.sprite = null;
		((Game*)game)->score.score += 10;
		eaten = true;
	}
}
