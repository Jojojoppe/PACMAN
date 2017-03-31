#include <Pacman.h>
#include <Game.h>

// Static objects
#include <Wall.h>
#include <Door.h>
#include <Tunnel.h>
#include <Dot.h>
#include <PowerPellet.h>
#include <Fruit.h>
#include <Ghostscore.h>

// Dynamic objects
#include <Ghost.h>

// Draw the sprites of pacman. Also keep track of the lives of pacman.
void Pacman::draw(){
	
	// When pacman is dead
	if(dead){
		
		if((counter++) % 2) return;		// delay of changes of the sprite
		
		// Create the animation. after the animation pacman is gone
		sprite.sprite = PacmanDyingS1;
		if(deadc<13) sprite.sprite += deadc++;	
		else{
			deadc++;
			sprite.sprite = null_empty;
		}
		
		// End of dead time
		if(deadc>30){
			// set ghost positions to start positions
			for(auto &i : ((Game *)game)->field){
				// Ghost
				if(dynamic_cast<Ghost*>(i)!=NULL){
					((Ghost*)i)->pos.x = 14*12;
					((Ghost*)i)->pos.y = 14*12;
				}
			}
			// Reset pacman variables
			dead = false;
			pos.x = 14*12;
			pos.y = 23*12;
			dir = left;
			ndir = left;
			sprite.sprite = PacmanEatRight1;
			deadc = 0;		
			
			// If all lives are gone -> RESET
			if(((Game*)game)->score.lives == 0) ((Game*)game)->resetGame();
		}	
		return;
	}
	
	// Change direction
	if(dir == up) sprite.sprite = PacmanEatUp1;
	if(dir == down) sprite.sprite = PacmanEatDown1;
	if(dir == left) sprite.sprite = PacmanEatLeft1;
	if(dir == right) sprite.sprite = PacmanEatRight1;
	if(open) sprite.sprite++;	// if open set PacmanX2
	
	// Open and close
	if((counter++) % 3) return;
	if(open){
		sprite.sprite--;
		open = false;
	}
	else{
		sprite.sprite++;
		open = true;
	}
}

// Move pacman
void Pacman::move(){
	
	if(dead) return;	// if pacman is dead, dont move
	
	// Backup old direction
	Direction dold = dir;
	
	// Move speed amount of pixels
	for(int i=0; i<speed; i++){
		
		// Backup old position
		Pos old = pos;
		
		// If there is a new direction check if there is no collision in that direction
		if(dir!=ndir){
			if(ndir == up) pos.y--;
			if(ndir == down) pos.y++;
			if(ndir == left) pos.x--;
			if(ndir == right) pos.x++;
			if(!checkCollision()) dir = ndir;	// No collision -> possible to go to that dir
			pos = old;	// after collisioncheck, return to old position
		}
		
		// Move one pixel
		if(dir == up) pos.y--;
		if(dir == down) pos.y++;
		if(dir == left) pos.x--;
		if(dir == right) pos.x++;
		if(checkCollision()) pos = old;			// If collision (hit a wall) stop
		
		// Tunnel
		if(pos.x<-12) pos.x = 12*28;
		if(pos.x>12*28) pos.x = -12;
		
	}	
}

// Collion check. Calls other functions when collission with objects, returns true if pacman cannot move through the object
bool Pacman::checkCollision(){
	
	// loop through the whole field
	for(auto &i : ((Game *)game)->field){
		
		// When the 12*12 square behing pacman is in the 12*12 square of another object -> collision
		if(pos.x<i->pos.x+12 && pos.x+12>i->pos.x && pos.y<i->pos.y+12 && pos.y+12>i->pos.y){
			
			// WALL
			if(dynamic_cast<Wall*>(i)!=NULL){
				return true;
			}
			
			// DOOR
			if(dynamic_cast<Door*>(i)!=NULL){
				return true;
			}
			
			// DOT
			if(dynamic_cast<Dot*>(i)!=NULL){
				((Dot*)i)->eat(game);
			}
			
			// PELLET
			if(dynamic_cast<PowerPellet*>(i)!=NULL){
				((PowerPellet*)i)->eat(game);
			}
			
			// FRUIT
			if(dynamic_cast<Fruit*>(i)!=NULL){
				((Fruit*)i)->eat(game);
			}
			
			// Ghost
			if(dynamic_cast<Ghost*>(i)!=NULL){
				
				// If pacman is not dead
				if(!dead){
					
					// and pacman has not eaten powerpellet -> pacman dies
					if(((Ghost*)i)->type==normal){
						((Game*)game)->score.lives--;
						dead = true;	
						
					// pacman has eaten powerpellet					
					}else if(((Ghost*)i)->type==frightened || ((Ghost*)i)->type==almostdead){
						// The ghost dies, changes to eyes
						((Ghost*)i)->type = (GhostType)(frightened+1);
						((Ghost*)i)->speed = 7;
						((Ghost*)i)->deadc = 0;
						// Powerscore is added
						((Game*)game)->score.add(powerscore);
						// Create the score popup object and add it to the field list
						Ghostscore * gs = new Ghostscore(powerscore, pos);
						((Game*)game)->field.push_back(gs);
						// Powerscore is multiplicated with 2 to get the sequence 200 400 800 1600 points
						powerscore += powerscore;
					}
				}
			}
			
		}
	}
	return false;
}

