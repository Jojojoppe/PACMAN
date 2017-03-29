#include <Blinky.h>
#include <Game.h>
#include <cstdlib>

void Blinky::move(){
	
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
		} else if(type==normal){
			vec.x = ((Game*)game)->pacman.pos.x - pos.x;
			vec.y = ((Game*)game)->pacman.pos.y - pos.y;
		} else{
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
		// Tunnel
		if(pos.x<-12) pos.x = 12*28;
		if(pos.x>12*28) pos.x = -12;
		
		if(tunnel){
			if(type==frightened || type==almostdead)
				speed = 1;
			else if(type==dead)
				speed = 5;
			else
				speed = 2;
		} else{
			if(type==frightened || type==almostdead)
				speed = 2;
			else if(type==dead)
				speed = 7;
			else
				speed = 4;
		}
	}
}
