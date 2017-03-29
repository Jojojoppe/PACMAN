#include "Score.h"
#include <Game.h>

void Score::reset(){
	lives = 3;
	score = 0;
	level = 0;
	fruitbonus = 0;
	extralife = false;
	dotseaten = 0;
}

void Score::add(int i){
	score += i;
	if(score>=10000 && !extralife){
		lives++;
		extralife = true;
	}
}

void Score::dot(){
	if(++dotseaten==242){
		dotseaten = 0;
		extralife = false;
		((Game*)game)->newLevel();
	}
}
