#pragma once

#include <DynamicObject.h>

enum GhostType{
	normal,
	frightened,
	dead,			// eyes
	almostdead		// blue-white
};

class Ghost : public DynamicObject{
	public:
		GhostType 	type = normal;
		bool 		tunnel = false;		// inside tunnel
		int			spritebase;
		bool 		tmspr = false;		// Sprites consists out of 2 state, this bool sets the state
		int 		deadc = 0;			// Timer for being blue and blue-white
		int 		counter = 0;		// Timer for sprite states
	
		Ghost(void * game);
		void draw() override;
		virtual void move();
		bool checkCollision();
};
