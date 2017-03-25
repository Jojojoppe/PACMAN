#pragma once

#include <Pos.h>
#include <Sprite.h>

enum ObjectType{
	null,
	wall,
	pacmanright,
	dot,
	pellet,
	pelletbig,
	door
};

class VisibleObject{
	public:
		Pos		pos;
		Sprite	sprite;
		
		virtual void draw();
};
