#include <Pacman.h>
#include <Game.h>
#include <Wall.h>
#include <Door.h>
#include <Tunnel.h>
#include <Dot.h>
#include <PowerPellet.h>
#include <Ghost.h>

#include <stdio.h>

void Pacman::draw(){
	
	if(dead){
		if((counter++) % 2) return;
		sprite.sprite = PacmanDyingS1;
		if(deadc<13) sprite.sprite += deadc++;	
		else{
			deadc++;
			sprite.sprite = null;
		}
		if(deadc>30){
			dead = false;
			pos.x = 14*12;
			pos.y = 23*12;
			dir = left;
			ndir = left;
			sprite.sprite = PacmanEatRight1;
			deadc = 0;
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
			
			// Ghost
			if(dynamic_cast<Ghost*>(i)!=NULL){
				if(!dead){
					((Game*)game)->score.lives--;
					dead = true;
				}
			}
			
		}
	}
	return false;
}
