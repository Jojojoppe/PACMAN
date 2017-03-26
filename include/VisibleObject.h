#pragma once

#include <Pos.h>
#include <Sprite.h>

enum ObjectType{
	null,

	// Specials
	dot,
	pellet,
	pelletbig,
	door,
	
	// All wall types
	wall1,
	wall2,
	wall3,
	wall4,
	wall5,
	wall6,
	wall7,
	wall8,
	wall9,
	wall10,
	wall11,
	wall12,
	wall13,
	wall14,
	wall15,
	wall16,
	wall17,
	wall18,
	wall19,
	wall20,
	wall21,
	wall22,
	wall23,
	wall24,
	wall25,
	wall26,
	wall27,
	wall28,
	wall29,
	wall30,
	wall31,
	wall32,
	wall33,
	wall34,
	wall35,
	wall36,
	wall37,
	wall38,
	wall39,
	wall40,
	wall41,
	wall42,
	wall43,
	wall44,
	wall45,
	wall46,
	
	// All numbers
	num0,
	num1,
	num2,
	num3,
	num4,
	num5,
	num6,
	num7,
	num8,
	num9,

	// Ghosts
	PinkyRight1,
	PinkyRight2,
	PinkyDown1,
	PinkyDown2,
	PinkyLeft1,
	PinkyLeft2,
	PinkyUp1,
	PinkyUp2,
	InkyRight1,
	InkyRight2,
	InkyDown1,
	InkyDown2,
	InkyLeft1,
	InkyLeft2,
	InkyUp1,
	InkyUp2,
	ClydeRight1,
	ClydeRight2,
	ClydeDown1,
	ClydeDown2,
	ClydeUp1,
	ClydeUp2,
	ClydeLeft1,
	ClydeLeft2,
	BlinkyRight1,
	BlinkyRight2,
	BlinkyDown1,
	BlinkyDown2,
	BlinkyLeft1,
	BlinkyLeft2,
	BlinkyUp1,
	BlinkyUp2,
	GhostDead1,
	GhostDead2,
	GhostAlmostDead1,
	GhostAlmostDead2,
	
	// Scores
	Score200,	
	Score400,	
	Score800,	
	Score1600,	
	
	// Pacman
	PacmanEatFull,
	PacmanEatRight1,
	PacmanEatRight2,
	PacmanEatDown1,
	PacmanEatDown2,
	PacmanEatUp1,
	PacmanEatUp2,
	PacmanEatLeft1,
	PacmanEatLeft2,
	PacmanDyingS1,
	PacmanDyingS2,
	PacmanDyingS3,
	PacmanDyingS4,
	PacmanDyingS5,
	PacmanDyingS6,
	PacmanDyingS7,
	PacmanDyingS8,
	PacmanDyingS9,
	PacmanDyingS10,
	PacmanDyingS11,
	PacmanDyingS12
};

class VisibleObject{;
	
	public:
		Pos		pos;
		Sprite	sprite;
		
		virtual void draw();
		
		void *	game;
		
};
