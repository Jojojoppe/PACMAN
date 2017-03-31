#pragma once

#include <Pos.h>

enum SpriteInfo{
	x,
	y,
	sizex,
	sizey
};

class Sprite {
	public:
		int 		sprite;
		Pos			pos;		// Relative drawing position towards object position
};
