#include "Fruit.h"
//The fruit should appear on the board, 
//it can be removed with the pushback function
void Fruit::draw(){
	
	if(Frtcnt < 160){
		Frtcnt++;
	}
	else if(Frtcnt >= 160 && Frtcnt < 301){
		Frtcnt++;
		sprite.sprite = FruitCherry;
		
	}
	if(Frtcnt = 300){
		((Game*)game)->field.pop_back();
		Frtcnt = 0;
	}
}

