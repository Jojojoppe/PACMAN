#pragma once

#include <DynamicObject.h>

class Game;

class Pacman : public DynamicObject{
	
	private:
		int 	counter = 0;
		bool 	open = false;
		
		bool	dead = false;
		int		deadc = 0;
	
	public:	
		void draw() override;
		void move();
		Direction 	ndir;
		bool checkCollision();
		int powerscore = 0;
};
