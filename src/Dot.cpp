#include "Dot.h"
#include <Game.h>

void Dot::eat(void * game){
	if(!eaten){
		sprite.sprite = null;
		((Game*)game)->score.add(10);
		((Game*)game)->score.dot();
		eaten = true;
	}
}
