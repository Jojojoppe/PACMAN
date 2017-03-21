#pragma once

#include <VisibleObject.h>

enum Direction{
	up,
	down,
	left,
	right
};

class DynamicObject : public VisibleObject {
	public:
		Direction 	dir;
		int			speed;
};
