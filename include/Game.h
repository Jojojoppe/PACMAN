#pragma once 

#include <vector>
#include <map>

#include <VisibleObject.h>
#include <Pacman.h>
#include <Score.h>

#include <SDL2/SDL.h>

enum ObjectType{
	wall,
	pacmanright
};

enum SpriteInfo{
	x,
	y,
	sizex,
	sizey
};

class Game{
	
	private:
		std::vector<VisibleObject> 	field;
		Score						score;
		
		// Graphic things
		SDL_Window *				window;
		SDL_Renderer *				renderer;
		SDL_Texture *				sheet;
		
		std::map<ObjectType,std::map<SpriteInfo,int>> spriteMap; 
		
		void loadSprites();	
	
	public:
		Pacman						pacman;
		
		SDL_TimerID					timer;
		
		void main();
		void resetGame();
		void newLevel();
		
		void refresh();
};

extern uint32_t refreshTimer(uint32_t interval, void * param);
