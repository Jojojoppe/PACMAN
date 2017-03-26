#include <Pacman.h>
#include <Game.h>
#include <Wall.h>

#include <stdio.h>

void Pacman::draw(){
	
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
	}	
}

bool Pacman::checkCollision(){
	for(auto &i : ((Game *)game)->field){
		if(pos.x<i->pos.x+12 && pos.x+12>i->pos.x && pos.y<i->pos.y+12 && pos.y+12>i->pos.y){
			// WALL
			if(dynamic_cast<Wall*>(i)!=NULL){
				return true;
			}
		}
	}
	return false;
}
