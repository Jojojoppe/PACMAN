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
	wall46
};

class VisibleObject{
	public:
		Pos		pos;
		Sprite	sprite;
		
		virtual void draw();
};
