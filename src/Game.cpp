#include <Game.h>
#include <maps.h>		// bitmaps

// StaticObjects
#include <Wall.h>
#include <Door.h>
#include <Tunnel.h>
#include <Dot.h>
#include <PowerPellet.h>

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
	
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
		}
	}
	SDL_RemoveTimer(timer);
	
}

void Game::resetGame(){
	
}

void Game::newLevel(){
	field.clear();
	SDL_RemoveTimer(timer);
	
	// Create map
	for(int i=0; i<map.size(); i++)
		for(int j=0; j<map[i].size(); j++){
			// Wall
			if(map[i][j]>=10 && map[i][j]<=32){
				Wall w;
				w.pos.x = j*24;
				w.pos.y = i*24;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Door
			if(map[i][j]==33){
				Door w;
				w.pos.x = j*24;
				w.pos.y = i*24;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Tunnel
			if(map[i][j]==34){
				Tunnel w;
				w.pos.x = j*24;
				w.pos.y = i*24;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// PowerPellet
			if(map[i][j]==2){
				PowerPellet w;
				w.pos.x = j*24;
				w.pos.y = i*24;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Dot
			if(map[i][j]==1){
				Dot w;
				w.pos.x = j*24;
				w.pos.y = i*24;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
		}
	
	// Add pacman
	pacman.pos.y = 23*24;
	pacman.pos.x = 14*24;
	pacman.dir = right;
	pacman.sprite.sprite = pacmanright;
	pacman.speed = 2;
	
	refresh();
	timer = SDL_AddTimer(50, refreshTimer, (void *)this);
	
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
	
	// Map map content to objectTypes
	mapToSprite[0] = null;
	mapToSprite[1] = null;		// dot
	mapToSprite[2] = null;		// power pellet
	mapToSprite[10] = wall;
	mapToSprite[11] = wall;
	mapToSprite[12] = wall;
	mapToSprite[13] = wall;
	mapToSprite[14] = wall;
	mapToSprite[15] = wall;
	mapToSprite[16] = wall;
	mapToSprite[17] = wall;
	mapToSprite[18] = wall;
	mapToSprite[19] = wall;
	mapToSprite[20] = wall;
	mapToSprite[21] = wall;
	mapToSprite[22] = wall;
	mapToSprite[23] = wall;
	mapToSprite[24] = wall;
	mapToSprite[25] = wall;
	mapToSprite[26] = wall;
	mapToSprite[27] = wall;
	mapToSprite[28] = null;
	mapToSprite[29] = wall;
	mapToSprite[30] = wall;
	mapToSprite[31] = wall;
	mapToSprite[32] = wall;	
	mapToSprite[33] = null;		// door
	mapToSprite[34] = null;		// tunnel
}

uint32_t refreshTimer(uint32_t interval, void * param){
	((Game*)param)->refresh();
	return interval;
}

void Game::refresh(){
	
	// Test movement
	pacman.pos.x -= pacman.speed;
	
	SDL_RenderClear(renderer);
	
	// Draw all objects
	for(auto &i : field){
		i.draw();
		SDL_Rect dst = {i.pos.x, i.pos.y, spriteMap[(ObjectType)i.sprite.sprite][sizex],spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_Rect src = {spriteMap[(ObjectType)i.sprite.sprite][x], spriteMap[(ObjectType)i.sprite.sprite][y], spriteMap[(ObjectType)i.sprite.sprite][sizex], spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw pacman
	pacman.draw();
	SDL_Rect dst = {pacman.pos.x, pacman.pos.y, spriteMap[(ObjectType)pacman.sprite.sprite][sizex],spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_Rect src = {spriteMap[(ObjectType)pacman.sprite.sprite][x], spriteMap[(ObjectType)pacman.sprite.sprite][y], spriteMap[(ObjectType)pacman.sprite.sprite][sizex], spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_RenderCopy(renderer, sheet, &src, &dst);
	
	SDL_RenderPresent(renderer);
}
