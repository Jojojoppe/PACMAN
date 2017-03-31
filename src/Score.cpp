#include "Score.h"
#include <Game.h>

// Reset the score
void Score::reset(){
	lives = 3;
	score = 0;
	level = 0;
	fruitbonus = 0;
	extralife = false;
	dotseaten = 0;
}

// Ad an amount of points to the score
void Score::add(int i){
	score += i;
	if(score>=10000 && !extralife){
		lives++;
		extralife = true;
	}
}

// When a dot is eaten the counter inceases
void Score::dot(){
	if(++dotseaten==242){
		dotseaten = 0;
		extralife = false;
		level++;
		((Game*)game)->newLevel();
	}
}
