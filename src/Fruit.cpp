#include "Fruit.h"
#include <Game.h>
#include <Score.h>

void Fruit::draw(){
	
	//Look for the level number -> each level the type should be different
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
	
	// Show fruit for 15 seconds
	if(Frtcnt < 300 && ((Game*)game)->score.dotseaten>72){
		Frtcnt++;
		if(!eaten)
			sprite.sprite = fruitCherry + (fruit-cherry);
		else
			sprite.sprite = null;
	}
	
	// After 15 seconds the fruit must dissappear
	if(Frtcnt == 300){
		sprite.sprite = null;
	}
	
}

// Eat the fruit
void Fruit::eat(void * game){
	if(!eaten && Frtcnt < 300 && ((Game*)game)->score.dotseaten>72){
		eaten = true;
		//If fruit is eaten add score
		switch (fruit){
			case cherry:
				((Game*)game)->score.add(100);
				((Game*)game)->score.fruitbonus = 0;
				break;
			case strawberry:
				((Game*)game)->score.add(200);
				((Game*)game)->score.fruitbonus = 1;
				break;
			case orange:
				((Game*)game)->score.add(300);
				((Game*)game)->score.fruitbonus = 2;
				break;
			case lemon:
				((Game*)game)->score.add(500);
				((Game*)game)->score.fruitbonus = 3;
				break;
			case apple:
				((Game*)game)->score.add(700); 
				((Game*)game)->score.fruitbonus = 4;
				break;
			case grapes:
				((Game*)game)->score.add(1000); 
				((Game*)game)->score.fruitbonus = 5;
				break;
			default:
				break;
		}
	}
}

