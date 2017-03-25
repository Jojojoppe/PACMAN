#pragma once

#include <StaticObject.h>

class PowerPellet : public StaticObject {
	private:
		int counter;
	public:
		PowerPellet();
		void draw() override;
};
