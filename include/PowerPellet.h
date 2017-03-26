#pragma once

#include <StaticObject.h>

class PowerPellet : public StaticObject {
	private:
		int counter = 0;
	public:
		PowerPellet();
		void draw() override;
};
