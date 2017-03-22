#pragma once

#include <Pos.h>
#include <Sprite.h>

enum ObjectType{
	null,
	wall,
	pacmanright
};

class VisibleObject{
	public:
		Pos		pos;
		Sprite	sprite;
		
		virtual void draw();
};
