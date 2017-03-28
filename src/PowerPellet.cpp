#include "PowerPellet.h"
#include <Game.h>

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
	}
}

for(auto &i : ((Game *)game)->field){
				
		// Ghost
		if(dynamic_cast<Ghost*>(i)!=NULL){
						
				//PowerPellet is eaten ghost is frightend. 
				((PowerPellet*)i) ->type = frightend;
				//The ghosts speed needs to change
				
				//Now Pacman is unfurnable for the ghosts 
			
			
				
			}
		}
	}
