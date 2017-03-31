#pragma once

#include <StaticObject.h>

class PowerPellet : public StaticObject {
	
	private:
		int 	counter = 0;		// Sprite timer to let the dots flashing
		bool 	eaten = false;
		
	public:
		PowerPellet();
		void draw() override;
		void eat(void * game);
		
};
