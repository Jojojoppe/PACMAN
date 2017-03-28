#include "PowerPellet.h"
#include <Game.h>
#include <Ghost.h>

PowerPellet::PowerPellet(){
	counter = 0;
}

void PowerPellet::draw(){
	if((counter++) % 10) return;
	if(sprite.sprite == pellet) sprite.sprite = pelletbig;
	else if(sprite.sprite == pelletbig) sprite.sprite = pellet;
}

void PowerPellet::eat(void * game){
	if(!eaten){
		sprite.sprite = null;
		((Game*)game)->score.score += 50;
		eaten = true;
		
		for(auto &i : ((Game *)game)->field){
					
			// Ghost
			if(dynamic_cast<Ghost*>(i)!=NULL){
							
				if(((Ghost*)i)->type == normal){
					//PowerPellet is eaten ghost is frightend. 
					((Ghost*)i)->type = frightened;
					//The ghosts speed needs to change
					//i represents every ghost
					((Ghost*)i)->speed = 2;
					((Ghost*)i)->sprite.sprite = GhostDead1;
									
					//Now Pacman is unfurnable for the ghosts 
					//If there is a collision ghost turns into eyes and score increases.
				
				}
			}
		}
	}
}


