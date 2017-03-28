#include <Ghost.h>
#include <Game.h>
#include <Wall.h>
#include <Tunnel.h>
#include <cstdlib>

void Ghost::draw(){
	
	if(type==normal){
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
	} else if(type==frightened){
		if((deadc++) == 80){
			type = almostdead;
			deadc = 0;
			sprite.sprite = GhostAlmostDead1;
			tmspr = false;
		}
	
		if((counter++) % 3) return;
		if(tmspr){ 
			sprite.sprite++;
			tmspr = false;
		}else{
			sprite.sprite--;
			tmspr = true;
		}
	}  else if(type==dead){
		sprite.sprite = eyesUp;
		// Change direction
		if(dir == up) sprite.sprite = eyesUp;
		if(dir == down) sprite.sprite = eyesDown;
		if(dir == left) sprite.sprite = eyesLeft;
		if(dir == right) sprite.sprite = eyesRight;
	} else if(type==almostdead){
		if((counter++) % 3) return;
		
		// Now not changing between 1 and 2 but white and blue!
		if(tmspr){ 
			sprite.sprite++;
			tmspr = false;
		}else{
			sprite.sprite--;
			tmspr = true;
		}
		if((deadc++) == 10){
			type = normal;
			deadc = 0;
			speed = 4;
			tmspr = false;
		}
	}
	
}

bool Ghost::checkCollision(){
	for(auto &i : ((Game *)game)->field){
		if(pos.x<i->pos.x+12 && pos.x+12>i->pos.x && pos.y<i->pos.y+12 && pos.y+12>i->pos.y){
			// WALL
			if(dynamic_cast<Wall*>(i)!=NULL){
				return true;
			}
			// TUNNEL
			if(dynamic_cast<Tunnel*>(i)!=NULL){
				return true;
			}
		}
	}
	return false;
}

void Ghost::move(){
	
	for(int i=0; i<speed; i++){	
		
		Pos vec;
		if(type==dead){
			vec.x = 13*12-pos.x;
			vec.y = 13*12-pos.y;
			if(vec.x == 0 && vec.y == 0){
				type = normal;
				deadc = 0;
				speed = 4;
				tmspr = false;
			}
		} else {
			vec.x = rand()%(12*28);
			vec.y = rand()%(12*31);
		}
		
		Pos old = pos;
		Direction dold = dir;
		
		if(abs(vec.x)>abs(vec.y)){
			if(vec.x<0) dir = left;
			else dir = right;
		} else{
			if(vec.y<0)	dir = up;
			else dir = down;
		}	
		
		// Not turning around
		if(dold==up && dir==down) dir = dold;
		else if(dold==down && dir==up) dir = dold;
		else if(dold==left && dir==right) dir = dold;
		else if(dold==right && dir==left) dir = dold;
		
		if(dir == up) pos.y--;
		if(dir == down) pos.y++;
		if(dir == left) pos.x--;
		if(dir == right) pos.x++;
		if(checkCollision()){
			pos = old;
			dir = dold;
			if(dir == up) pos.y--;
			if(dir == down) pos.y++;
			if(dir == left) pos.x--;
			if(dir == right) pos.x++;
			if(checkCollision()){
				pos = old;
				// now pick random direction
				dold = dir;
				while(1){
					dir = (Direction)(up+rand()%4);
					if(dold==up && dir==down) continue;
					if(dold==down && dir==up) continue;
					if(dold==left && dir==right) continue;
					if(dold==right && dir==left) continue;
					
					// Check if new direction is oke
					if(dir == up) pos.y--;
					if(dir == down) pos.y++;
					if(dir == left) pos.x--;
					if(dir == right) pos.x++;
					if(checkCollision()){
						pos = old;
						continue;
					}
					
					// Yes new direction found
					break;
				}
			}
		}
	}
}
