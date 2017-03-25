#include <Game.h>
#include <maps.h>

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
							  12*28, 12*31+1*24,
							  SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Load sprite sheet
	SDL_Surface *surf = SDL_LoadBMP("resources/sam_gfx.bmp");
	sheet = SDL_CreateTextureFromSurface(renderer, surf);
	if (sheet == nullptr) 
		std::cout << " error: " << SDL_GetError();
	loadSprites();
	
	resetGame();
	
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
	score.reset();
	newLevel();
}

void Game::newLevel(){
	field.clear();
	SDL_RemoveTimer(timer);
	score.reset();
	
	// Create map
	for(int i=0; i<map.size(); i++)
		for(int j=0; j<map[i].size(); j++){
			// Wall
			if(map[i][j]>=10 && map[i][j]<=32){
				Wall w;
				w.pos.x = j*12;
				w.pos.y = i*12;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Door
			if(map[i][j]==33){
				Door w;
				w.pos.x = j*12;
				w.pos.y = i*12;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Tunnel
			if(map[i][j]==34){
				Tunnel w;
				w.pos.x = j*12;
				w.pos.y = i*12;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// PowerPellet
			if(map[i][j]==2){
				PowerPellet w;
				w.pos.x = j*12;
				w.pos.y = i*12;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Dot
			if(map[i][j]==1){
				Dot w;
				w.pos.x = j*12;
				w.pos.y = i*12;
				w.sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
		}
	
	// Add pacman
	pacman.pos.y = 23*12;
	pacman.pos.x = 14*12;
	pacman.dir = right;
	pacman.sprite.sprite = pacmanright;
	pacman.sprite.pos.x = -6;
	pacman.sprite.pos.y = -6;
	pacman.speed = 0;
	
	refresh();
	timer = SDL_AddTimer(50, refreshTimer, (void *)this);
	
}

void Game::loadSprites(){
		
	spriteMap[wall][x] = 4+6*24;
	spriteMap[wall][y] = 4+11*24;
	spriteMap[wall][sizex] = 12;
	spriteMap[wall][sizey] = 12;
	
	spriteMap[pacmanright][x] = 4+0*24;
	spriteMap[pacmanright][y] = 5+11*24;
	spriteMap[pacmanright][sizex] = 24;
	spriteMap[pacmanright][sizey] = 24;
	
	spriteMap[dot][x] = 4+16*12;
	spriteMap[dot][y] = 5;
	spriteMap[dot][sizex] = 12;
	spriteMap[dot][sizey] = 12;
	
	spriteMap[pellet][x] = 4+18*12;
	spriteMap[pellet][y] = 5;
	spriteMap[pellet][sizex] = 12;
	spriteMap[pellet][sizey] = 12;
	
	spriteMap[pelletbig][x] = 4+20*12;
	spriteMap[pelletbig][y] = 5;
	spriteMap[pelletbig][sizex] = 12;
	spriteMap[pelletbig][sizey] = 12;
	
	spriteMap[door][x] = 4+15*12;
	spriteMap[door][y] = 4+6*12;
	spriteMap[door][sizex] = 12;
	spriteMap[door][sizey] = 12;
	
	// Map map content to objectTypes
	mapToSprite[0] = null;
	mapToSprite[1] = dot;		// dot
	mapToSprite[2] = pellet;		// power pellet
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
	mapToSprite[33] = door;		// door
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
		SDL_Rect dst = {i.pos.x+i.sprite.pos.x, i.pos.y+i.sprite.pos.y, spriteMap[(ObjectType)i.sprite.sprite][sizex],spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_Rect src = {spriteMap[(ObjectType)i.sprite.sprite][x], spriteMap[(ObjectType)i.sprite.sprite][y], spriteMap[(ObjectType)i.sprite.sprite][sizex], spriteMap[(ObjectType)i.sprite.sprite][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw pacman
	pacman.draw();
	SDL_Rect dst = {pacman.pos.x+pacman.sprite.pos.x, pacman.pos.y+pacman.sprite.pos.y, spriteMap[(ObjectType)pacman.sprite.sprite][sizex],spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_Rect src = {spriteMap[(ObjectType)pacman.sprite.sprite][x], spriteMap[(ObjectType)pacman.sprite.sprite][y], spriteMap[(ObjectType)pacman.sprite.sprite][sizex], spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_RenderCopy(renderer, sheet, &src, &dst);
	
	// Draw amount of lives
	for(int i=0;i<score.lives;i++){
		SDL_Rect dst = {2*24-i*24, 31*12, spriteMap[pacmanright][sizex], spriteMap[pacmanright][sizey]};
		SDL_Rect src = {spriteMap[pacmanright][x], spriteMap[pacmanright][y], spriteMap[pacmanright][sizex], spriteMap[pacmanright][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw fruitbonus
	if(score.fruitbonus){
		SDL_Rect dst = {4*24, 31*12, spriteMap[pacmanright][sizex], spriteMap[pacmanright][sizey]};
		SDL_Rect src = {spriteMap[pacmanright][x], spriteMap[pacmanright][y], spriteMap[pacmanright][sizex], spriteMap[pacmanright][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw score
	int digitSelector = 1;
	int digit = 0;
	int value;
	while(digitSelector < 100000){
		SDL_Rect dst = {13*24-digit*24, 31*12, 24,24};
		SDL_Rect src = {spriteMap[pacmanright][x], spriteMap[pacmanright][y], spriteMap[pacmanright][sizex], spriteMap[pacmanright][sizey]};
		value = (score.score/digitSelector)%10;
		SDL_RenderCopy(renderer, sheet, &src, &dst);
		digitSelector *= 10;
		digit++;
	}
	
	SDL_RenderPresent(renderer);
}

