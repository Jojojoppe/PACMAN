#pragma once

#include <VisibleObject.h>

enum Direction{
	up,
	down,
	left,
	right
};

class DynamicObject : public VisibleObject {
	private:
		int			mcnt = 0;
	public:
		Direction 	dir;
		int			speed;
};
