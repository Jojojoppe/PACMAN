#pragma once

#include <DynamicObject.h>

class Game;

class Pacman : public DynamicObject{
	
	private:
		int 	counter = 0;
		bool 	open = false;
		
		bool checkCollision();
	
	public:
		Direction 	ndir;
	
		void draw() override;
		void move();
};
