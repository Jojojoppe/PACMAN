#pragma once

#include <DynamicObject.h>

enum GhostType{
	normal,
	frightened,
	dead,
	almostdead
};

class Ghost : public DynamicObject{
	public:
		void draw() override;
		int		spritebase;
		virtual void move();
		GhostType type = normal;
		bool tmspr = false;
		int deadc = 0;
		bool checkCollision();
		int counter = 0;
};
