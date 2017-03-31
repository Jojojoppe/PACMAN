#include <Blinky.h>
#include <Game.h>
#include <cstdlib>

// Move function of blinky
void Blinky::move(){
	
	// move speed amount of pixels
	for(int i=0; i<speed; i++){		
		
		// Get the point where to go: when dead goto home. else follow pacman. When frightened pick a random direction
		// the vec position is used as vector to the wanted position.
		Pos vec;
		if(type==dead){
			vec.x = 13*12-pos.x;
			vec.y = 13*12-pos.y;
			if(vec.x == 0 && vec.y == 0){
				// When reached home go back to normal
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
			
		// Backup the old direction and position
		Pos old = pos;
		Direction dold = dir;
		
		// Decide which way to go. Take the direction of the smallest component (x or y).
		if(abs(vec.x)>abs(vec.y)){
			if(vec.x<0) dir = left;
			else dir = right;
		} else{
			if(vec.y<0)	dir = up;
			else dir = down;
		}	
		
		// Not turning around! So when the wanted direction means turning around go straigh ahead
		if(dold==up && dir==down) dir = dold;
		else if(dold==down && dir==up) dir = dold;
		else if(dold==left && dir==right) dir = dold;
		else if(dold==right && dir==left) dir = dold;
		
		// Move one pixel to that direction and checks for collision
		if(dir == up) pos.y--;
		if(dir == down) pos.y++;
		if(dir == left) pos.x--;
		if(dir == right) pos.x++;
		if(checkCollision()){
			
			// Collision in the wanted direction, go to old position and direction
			pos = old;
			dir = dold;
			
			// Move one pixel in old direction
			if(dir == up) pos.y--;
			if(dir == down) pos.y++;
			if(dir == left) pos.x--;
			if(dir == right) pos.x++;
			if(checkCollision()){
				
				// Collision in old direction -> pick randon direction
				
				// Goto old position and backup direction
				pos = old;
				dold = dir;
				
				// Find a usable direction
				while(1){
					
					// Take random direction
					dir = (Direction)(up+rand()%4);
					
					// if this means turning around find another one
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
						// No -> collision, goto old position and find another one
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
		
		// If inside a tunnel, change to proper speeds
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
