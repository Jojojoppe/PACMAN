#include "Fruit.h"
#include <Game.h>
#include <Score.h>

//The fruit should appear on the board, 
//it can be removed with the pushback function
void Fruit::draw(){
	//Look for the level number
	switch (((Game*)game)->score.level){
		case 0:
			fruit = cherry;
			break;
		case 1:
			fruit = strawberry;
			break;
		case 2:
		case 3:
			fruit = orange;
			break;
		case 4:
		case 5:
			fruit = lemon;
			break;
		case 6:
		case 7:
			fruit = apple; 
			break;
		case 8:
		case 9:
			fruit = grapes; 
			break;
		default:
			fruit = grapes;
			break;
	}
	
	//if(Frtcnt < 160){
	//	Frtcnt++;
	//}
	if(Frtcnt < 300 && ((Game*)game)->score.dotseaten>72){
		Frtcnt++;
		if(!eaten)
			sprite.sprite = fruitCherry + (fruit-cherry);
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
	if(!eaten && Frtcnt < 300 && ((Game*)game)->score.dotseaten>72){
		eaten = true;
		//If fruit is eaten add score
		switch (fruit){
			case cherry:
				((Game*)game)->score.add(100);
				((Game*)game)->score.fruitbonus = 100;
				break;
			case strawberry:
				((Game*)game)->score.add(200);
				((Game*)game)->score.fruitbonus = 200;
				break;
			case orange:
				((Game*)game)->score.add(300);
				((Game*)game)->score.fruitbonus = 300;
				break;
			case lemon:
				((Game*)game)->score.add(500);
				((Game*)game)->score.fruitbonus = 500;
				break;
			case apple:
				((Game*)game)->score.add(700); 
				((Game*)game)->score.fruitbonus = 700;
				break;
			case grapes:
				((Game*)game)->score.add(1000); 
				((Game*)game)->score.fruitbonus = 1000;
				break;
			default:
				break;
		}
	}
}

