#pragma once

class Score {	
	private:
		bool 	extralife;
		
	public:
	
		int		score;
		int		lives;
		int 	fruitbonus;
		int 	level;
		int 	dotseaten;
		
		void *	game;			// Pointer to the game object
	
		void 	reset();
		void	add(int i);
		void	dot();			// Eat a dot
		
};
