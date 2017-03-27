#pragma once

#include <vector>
#include <map>

#include <VisibleObject.h>

#include <Sprite.h>
#include <Pacman.h>
#include <Score.h>

#include <SDL2/SDL.h>

class Game{
	
	private:
		
		// Graphic things
		SDL_Window *				window;
		SDL_Renderer *				renderer;
		SDL_Texture *				sheet;
		
		// Sprite mappings -> thinking: outisde or inside class
		std::map<ObjectType,std::map<SpriteInfo,int>> spriteMap; 
		std::map<int, ObjectType> mapToSprite;
		std::map<int, ObjectType> numToSprite;
		
		void loadSprites();	
		
		void drawScore();
		
		SDL_TimerID					timer;
	
	public:
		Pacman						pacman;
		std::vector<VisibleObject*> 	field;
		Score						score;
		
		void refresh();
		
		void main();
		void resetGame();
		void newLevel();
};

extern uint32_t refreshTimer(uint32_t interval, void * param);
