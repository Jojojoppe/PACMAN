#pragma once

#include <StaticObject.h>

class Dot : public StaticObject {
	
	private:
		bool eaten = false;
		
	public:
		void eat(void * game);
		
};
