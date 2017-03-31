#pragma once

#include <StaticObject.h>
enum FruitType{
	cherry,
	strawberry,
	orange,
	lemon,
	apple,
	grapes,
	nofruit
};

class Fruit : public StaticObject{
	
	private:
		int Frtcnt = 0;			// Timer counter for fruit (visible time)
		bool eaten = false;
	
	public:
		FruitType fruit = nofruit;
	
		void draw() override;
		void eat(void * game);
		
};
