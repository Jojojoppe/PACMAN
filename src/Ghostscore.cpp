#include <Ghostscore.h>

// When added to the field, initiate
Ghostscore::Ghostscore(int s, Pos p){
	pos.x = p.x;
	pos.y = p.y;
	sprite.pos.x = -6;
	counter = 0;
	score = s;
}

// Show the score for 1.5 seconds
void Ghostscore::draw(){
	switch(score){
		case 200:
			sprite.sprite = Score200;
		break;
		case 400:
			sprite.sprite = Score400;
		break;
		case 800:
			sprite.sprite = Score800;
		break;
		case 1600:
			sprite.sprite = Score1600;
		break;
	}
	if(counter++>30) sprite.sprite = null_empty;
}
