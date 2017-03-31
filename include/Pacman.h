#pragma once

#include <DynamicObject.h>

class Game;

class Pacman : public DynamicObject{
	
	private:
		int 		counter = 0;		// Sprite timer
		bool 		open = false;		// Pacman sprite consists out of open and close states
		bool		dead = false;
		int			deadc = 0;	 		// Timer for waiting to start over
	
	public:	
		Direction 	ndir;				// Next direction, set by the main routine	
		int 		powerscore = 0;		// Score when eating ghosts (inceament with power)	
	
		void draw() override;
		void move();
		bool checkCollision();
};
