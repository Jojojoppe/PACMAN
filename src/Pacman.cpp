#include <Pacman.h>
#include <Game.h>
#include <Wall.h>
#include <Door.h>
#include <Tunnel.h>
#include <Dot.h>
#include <PowerPellet.h>
#include <Ghost.h>
#include <Fruit.h>
#include <Ghostscore.h>

#include <stdio.h>

void Pacman::draw(){
	
	if(dead){
		if((counter++) % 2) return;
		sprite.sprite = PacmanDyingS1;
		if(deadc<13) sprite.sprite += deadc++;	
		// Dead timer
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

void Pacman::move(){
	
	if(dead) return;
	
	Direction dold = dir;
	
	for(int i=0; i<speed; i++){
		Pos old = pos;
		if(dir!=ndir){
			if(ndir == up) pos.y--;
			if(ndir == down) pos.y++;
			if(ndir == left) pos.x--;
			if(ndir == right) pos.x++;
			if(!checkCollision()) dir = ndir;
			pos = old;
		}
		
		if(dir == up) pos.y--;
		if(dir == down) pos.y++;
		if(dir == left) pos.x--;
		if(dir == right) pos.x++;
		if(checkCollision()) pos = old;
		
		// Tunnel
		if(pos.x<-12) pos.x = 12*28;
		if(pos.x>12*28) pos.x = -12;
		
	}	
}

bool Pacman::checkCollision(){
	for(auto &i : ((Game *)game)->field){
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
				if(!dead){
					if(((Ghost*)i)->type==normal){
						((Game*)game)->score.lives--;
						dead = true;						
					}else if(((Ghost*)i)->type==frightened || ((Ghost*)i)->type==almostdead){
						((Ghost*)i)->type = (GhostType)(frightened+1);
						((Ghost*)i)->speed = 7;
						((Ghost*)i)->deadc = 0;
						((Game*)game)->score.add(powerscore);
						Ghostscore * gs = new Ghostscore(powerscore, pos);
						((Game*)game)->field.push_back(gs);
						powerscore += powerscore;
					}
				}
			}
			
		}
	}
	return false;
}
