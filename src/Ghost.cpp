#include <Ghost.h>
#include <Game.h>
#include <Wall.h>

void Ghost::draw(){
	// Change direction
	if(dir == up) sprite.sprite = spritebase;
	if(dir == down) sprite.sprite = spritebase+2;
	if(dir == left) sprite.sprite = spritebase+4;
	if(dir == right) sprite.sprite = spritebase+6;
	if(tmspr) sprite.sprite++;	// if open set GhostXY2
	
	// Open and close
	if((counter++) % 3) return;
	if(tmspr){
		sprite.sprite--;
		tmspr = false;
	}
	else{
		sprite.sprite++;
		tmspr = true;
	}
}

bool Ghost::checkCollision(){
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

void Ghost::move(){
		
	for(int i=0; i<speed; i++){
		Pos old = pos;
				
		if(dir == up) pos.y--;
		if(dir == down) pos.y++;
		if(dir == left) pos.x--;
		if(dir == right) pos.x++;
		if(checkCollision()){
			pos = old;
			
			// Change direction
			Direction dold = dir;
			while(1){
				dir = (Direction)(up+rand()%4);
				if(dold==up && dir==down) continue;
				if(dold==down && dir==up) continue;
				if(dold==left && dir==right) continue;
				if(dold==right && dir==left) continue;
				break;
			}
		}
		
		// Tunnel
		if(pos.x<-12) pos.x = 12*28;
		if(pos.x>12*28) pos.x = -12;
		
	}	
}
