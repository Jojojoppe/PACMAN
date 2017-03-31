#pragma once

#include <Ghost.h>

class Blinky : public Ghost{
	
	public:
		using Ghost::Ghost;
		void move() override;
		
};
