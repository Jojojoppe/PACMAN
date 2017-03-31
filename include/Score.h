#pragma once

class Score {	
	private:
		bool 	extralife;
		
	public:
		void 	reset();
		void	add(int i);
		void	dot();
		
		int		score;
		int		lives;
		int 	fruitbonus;
		int 	level;
		
		int 	dotseaten;
		
		void *	game;
		
};
