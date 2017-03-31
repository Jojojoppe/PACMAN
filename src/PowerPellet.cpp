#include "PowerPellet.h"
#include <Game.h>
#include <Ghost.h>

PowerPellet::PowerPellet(){
	counter = 0;
}

// Let powerpellet flash
void PowerPellet::draw(){
	if((counter++) % 10) return;
	if(sprite.sprite == pellet) sprite.sprite = pelletbig;
	else if(sprite.sprite == pelletbig) sprite.sprite = pellet;
}

// When eaten, dissappear, loop through the field to find the ghosts and make them frightened
void PowerPellet::eat(void * game){
	if(!eaten){
		sprite.sprite = null;
		((Game*)game)->score.add(50);
		eaten = true;
		
		((Game *)game)->pacman.powerscore = 200;
		
		// Loop through field
		for(auto &i : ((Game *)game)->field){
					
			// normal or frightened ghost is found
			if(dynamic_cast<Ghost*>(i)!=NULL && (((Ghost*)i)->type == normal || ((Ghost*)i)->type == frightened || ((Ghost*)i)->type == almostdead)){
				//PowerPellet is eaten ghost is frightend. 
				((Ghost*)i)->type = frightened;
				//The ghosts speed needs to change
				((Ghost*)i)->speed = 2;
				((Ghost*)i)->sprite.sprite = GhostDead1;
				((Ghost*)i)->tmspr = true;
				((Ghost*)i)->deadc = 0;
				
				// Reverse direction of ghosts
				if(((Ghost*)i)->dir == up) ((Ghost*)i)->dir = down;
				if(((Ghost*)i)->dir == down) ((Ghost*)i)->dir = up;
				if(((Ghost*)i)->dir == right) ((Ghost*)i)->dir = left;
				if(((Ghost*)i)->dir == left) ((Ghost*)i)->dir = right;
								
				//Now Pacman is unfurnable for the ghosts 
				//If there is a collision ghost turns into eyes and score increases.
			}
		}
	}
}


