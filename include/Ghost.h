#pragma once

#include <DynamicObject.h>

enum GhostType{
	normal,
	frightened,
	dead
};

class Ghost : public DynamicObject{
	private:
		bool tmspr = false;
		int counter = 0;
		bool checkCollision();
		int deadc = 0;
	public:
		void draw() override;
		int		spritebase;
		void move();
		GhostType type = normal;
};
