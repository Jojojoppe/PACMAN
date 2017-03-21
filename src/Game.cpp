#include <Game.h>
#include <maps.h>		// bitmaps

#include <Wall.h>
#include <Pacman.h>

#include <iostream>

void Game::main(){
	// Initialize window
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Programming 2: PACMAN",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  24*28, 24*31+3*24,
							  SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Load sprite sheet
	SDL_Surface *surf = SDL_LoadBMP("resources/sam_gfx.bmp");
	sheet = SDL_CreateTextureFromSurface(renderer, surf);
	if (sheet == nullptr) 
		std::cout << " error: " << SDL_GetError();
	loadSprites();
	
	resetGame();
	newLevel();
}

void Game::resetGame(){
	
}

void Game::newLevel(){
	field.clear();
	SDL_RemoveTimer(timer);
	
	// Create walls
	for(int i=0; i<map.size(); i++)
		for(int j=0; j<map[i].size(); j++)
			if(map[i][j]==1){
				Wall w;
				w.pos.x = j;
				w.pos.y = i;
				w.sprite.sprite = wall;
				field.push_back(w);
			}
	
	// Add pacman
	pacman.pos.y = 23;
	pacman.pos.x = 14;
	pacman.dir = right;
	pacman.sprite.sprite = pacmanright;
	field.push_back(pacman);
	
	refresh();
	timer = SDL_AddTimer(100, refreshTimer, (void *)this);
	
}

void Game::loadSprites(){
	spriteMap[wall][x] = 4+6*24;
	spriteMap[wall][y] = 4+11*24;
	spriteMap[wall][sizex] = 24;
	spriteMap[wall][sizey] = 24;
	
	spriteMap[pacmanright][x] = 4+0*24;
	spriteMap[pacmanright][y] = 4+11*24;
	spriteMap[pacmanright][sizex] = 24;
	spriteMap[pacmanright][sizey] = 24;
}

uint32_t refreshTimer(uint32_t interval, void * param){
	((Game*)param)->refresh();
	return interval;
}

void Game::refresh(){
	SDL_RenderClear(renderer);
	for(auto &i : field){
		i.draw();
		SDL_Rect dst = {i.pos.x*24, i.pos.y*24, spriteMap[(ObjectType)i.sprite.sprite][sizex],spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_Rect src = {spriteMap[(ObjectType)i.sprite.sprite][x], spriteMap[(ObjectType)i.sprite.sprite][y], spriteMap[(ObjectType)i.sprite.sprite][sizex], spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	SDL_RenderPresent(renderer);
}
