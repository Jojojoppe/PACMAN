#include "Dot.h"
#include <Game.h>

// When dot is eaten, go black and do not respond to collissions anymore
void Dot::eat(void * game){
	if(!eaten){
		sprite.sprite = null;
		((Game*)game)->score.add(10);
		((Game*)game)->score.dot();
		eaten = true;
	}
}
