#pragma once

#include <Ghost.h>

class Pinky : public Ghost{
	
	public:
		using Ghost::Ghost;
		void move() override;
		
};
