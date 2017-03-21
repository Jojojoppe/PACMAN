#pragma once

#include <Pos.h>
#include <Sprite.h>

class VisibleObject{
	public:
		Pos		pos;
		Sprite	sprite;
		
		virtual void draw();
};
