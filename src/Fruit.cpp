#include "Fruit.h"
#include <Game.h>
//The fruit should appear on the board, 
//it can be removed with the pushback function
void Fruit::draw(){
	
	if(Frtcnt < 160){
		Frtcnt++;
	}
	else if(Frtcnt >= 160 && Frtcnt < 300){
		Frtcnt++;
		if(!eaten)
			sprite.sprite = fruitCherry;
		else
			sprite.sprite = null;
	}
	if(Frtcnt == 300){
		//((Game*)game)->field.pop_back();
		sprite.sprite = null;
		//Frtcnt = 0;
	}
	
}

void Fruit::eat(void * game){
	if(!eaten && Frtcnt >=160 && Frtcnt < 300){
		eaten = true;
		((Game*)game)->score.add(100);
		((Game*)game)->score.fruitbonus = 100;
	}
}

