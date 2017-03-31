#pragma once

#include <StaticObject.h>
#include <Pos.h>

class Ghostscore : public StaticObject{
	private:
		int counter = 0;
		int score = 0;
	public:
		Ghostscore(int score, Pos p);
		void draw() override;
};
