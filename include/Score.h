#pragma once

class Score {	
	private:
		bool 	extralife;
		int 	dotseaten;
		
	public:
		void 	reset();
		void	add(int i);
		void	dot();
		
		int		score;
		int		lives;
		int 	fruitbonus;
		int 	level;
		
		void *	game;
		
};
