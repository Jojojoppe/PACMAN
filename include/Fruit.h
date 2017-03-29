#pragma once

#include <StaticObject.h>
enum FruitType{
	cherry,
	strawberry,
	orange,
	lemon,
	apple,
	grapes
};

class Fruit : public StaticObject{
	private:
		int Frtcnt = 0;
		bool eaten = false;
	
	public:
		void draw() override;
		void eat(void * game);
};
