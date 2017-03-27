#pragma once

#include <StaticObject.h>

class PowerPellet : public StaticObject {
	private:
		int counter = 0;
		bool eaten = false;
	public:
		PowerPellet();
		void draw() override;
		void eat(void * game);
};
