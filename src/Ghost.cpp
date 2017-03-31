#include <Ghost.h>
#include <Game.h>
#include <Wall.h>
#include <Tunnel.h>
#include <cstdlib>

// Draw the ghost
void Ghost::draw(){
	
	// If normal ghost
	if(type==normal){
		
		// Change direction. Each direction has 2 sprites so for directions multiplants of 2 are added to spritebase, the first sprite upwards
		if(dir == up) sprite.sprite = spritebase;
		if(dir == down) sprite.sprite = spritebase+2;
		if(dir == left) sprite.sprite = spritebase+4;
		if(dir == right) sprite.sprite = spritebase+6;
		if(tmspr) sprite.sprite++;	// if second sprite set GhostXY2
		
		if((counter++) % 3) return;		// Delay for changing between sprite versions
		
		// Change sprite version (1 and 2)
		if(tmspr){
			sprite.sprite--;
			tmspr = false;
		}
		else{
			sprite.sprite++;
			tmspr = true;
		}
		
	// Frightened ghost
	} else if(type==frightened){
		
		// After 80 ticks the ghost should go blue-white
		if((deadc++) == 80){
			type = almostdead;
			deadc = 0;
			sprite.sprite = GhostAlmostDead1;
			tmspr = false;
		}
	
		if((counter++) % 3) return;		// Delay for changing between sprite versions
		
		if(tmspr){ 
			sprite.sprite++;
			tmspr = false;
		}else{
			sprite.sprite--;
			tmspr = true;
		}
		
	// Ghost is dead
	}  else if(type==dead){
		
		sprite.sprite = eyesUp;
		// Change direction
		if(dir == up) sprite.sprite = eyesUp;
		if(dir == down) sprite.sprite = eyesDown;
		if(dir == left) sprite.sprite = eyesLeft;
		if(dir == right) sprite.sprite = eyesRight;
		
	// Ghost is blue-white
	} else if(type==almostdead){
		
		if((counter++) % 3) return;		// Delay between going blue and white
		
		// Now not changing between 1 and 2 but white and blue!
		if(tmspr){ 
			sprite.sprite++;
			tmspr = false;
		}else{
			sprite.sprite--;
			tmspr = true;
		}
		
		// After 10 ticks goto normal state again
		if((deadc++) == 10){
			type = normal;
			deadc = 0;
			speed = 4;
			tmspr = false;
		}
	}
	
}

// Check collision. Works in the same way as pacman's checkCollision function
bool Ghost::checkCollision(){
	
	// Not in tunnel, changed in the loop if so
	tunnel = false;
	
	for(auto &i : ((Game *)game)->field){
		if(pos.x<i->pos.x+12 && pos.x+12>i->pos.x && pos.y<i->pos.y+12 && pos.y+12>i->pos.y){
			// WALL
			if(dynamic_cast<Wall*>(i)!=NULL){
				return true;
			}
			// TUNNEL
			if(dynamic_cast<Tunnel*>(i)!=NULL){
				tunnel = true;
			}
		}
	}
	return false;
}

// Move function of the ghosts. Pinky and Blinky have their own functions (almost the same as this)
void Ghost::move(){
	
	// move speed amount of pixels
	for(int i=0; i<speed; i++){	
		
		// Get the point where to go: when dead goto home. else pick a random spot.
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
		}else {
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

// Constructor: set default things
Ghost::Ghost(void * g){
	pos.x = 14*12;
	pos.y = 14*12;
	dir = up;
	sprite.pos.x = -6;
	sprite.pos.y = -6;
	speed = 4;
	game = (Game*) g;
}
