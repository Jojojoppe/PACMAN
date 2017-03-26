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
	
	// Delete all objects
	for(auto &i : field)
		delete i;
	field.clear();
	
	SDL_RemoveTimer(timer);
	score.reset();
	
	// Create map
	for(int i=0; i<map.size(); i++)
		for(int j=0; j<map[i].size(); j++){
			// Wall
			if(map[i][j]>=10 && map[i][j]<=32){
				Wall * w = new Wall;
				w->pos.x = j*12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Door
			if(map[i][j]==33){
				Door * w = new Door;
				w->pos.x = j*12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Tunnel
			if(map[i][j]==34){
				Tunnel * w = new Tunnel;
				w->pos.x = j*12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// PowerPellet
			if(map[i][j]==2){
				PowerPellet * w = new PowerPellet;
				w->pos.x = j*12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Dot
			if(map[i][j]==1){
				Dot * w = new Dot;
				w->pos.x = j*12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
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
	
	// All wall types
	spriteMap[wall1][x] = 4+16*12;
	spriteMap[wall1][y] = 4+6*12;
	spriteMap[wall1][sizex] = 12;
	spriteMap[wall1][sizey] = 12;
	
	spriteMap[wall2][x] = 4+17*12;
	spriteMap[wall2][y] = 4+6*12;
	spriteMap[wall2][sizex] = 12;
	spriteMap[wall2][sizey] = 12;
	
	spriteMap[wall3][x] = 4+18*12;
	spriteMap[wall3][y] = 4+6*12;
	spriteMap[wall3][sizex] = 12;
	spriteMap[wall3][sizey] = 12;
	
	spriteMap[wall4][x] = 4+19*12;
	spriteMap[wall4][y] = 4+6*12;
	spriteMap[wall4][sizex] = 12;
	spriteMap[wall4][sizey] = 12;
	
	spriteMap[wall5][x] = 4+20*12;
	spriteMap[wall5][y] = 4+6*12;
	spriteMap[wall5][sizex] = 12;
	spriteMap[wall5][sizey] = 12;

	spriteMap[wall6][x] = 4+21*12;
	spriteMap[wall6][y] = 4+6*12;
	spriteMap[wall6][sizex] = 12;
	spriteMap[wall6][sizey] = 12;

	spriteMap[wall7][x] = 4+22*12;
	spriteMap[wall7][y] = 4+6*12;
	spriteMap[wall7][sizex] = 12;
	spriteMap[wall7][sizey] = 12;

	spriteMap[wall8][x] = 4+23*12;
	spriteMap[wall8][y] = 4+6*12;
	spriteMap[wall8][sizex] = 12;
	spriteMap[wall8][sizey] = 12;

	spriteMap[wall9][x] = 4+24*12;
	spriteMap[wall9][y] = 4+6*12;
	spriteMap[wall9][sizex] = 12;
	spriteMap[wall9][sizey] = 12;

	spriteMap[wall10][x] = 4+25*12;
	spriteMap[wall10][y] = 4+6*12;
	spriteMap[wall10][sizex] = 12;
	spriteMap[wall10][sizey] = 12;

	spriteMap[wall11][x] = 4+26*12;
	spriteMap[wall11][y] = 4+6*12;
	spriteMap[wall11][sizex] = 12;
	spriteMap[wall11][sizey] = 12;

	spriteMap[wall12][x] = 4+27*12;
	spriteMap[wall12][y] = 4+6*12;
	spriteMap[wall12][sizex] = 12;
	spriteMap[wall12][sizey] = 12;

	spriteMap[wall13][x] = 4+28*12;
	spriteMap[wall13][y] = 4+6*12;
	spriteMap[wall13][sizex] = 12;
	spriteMap[wall13][sizey] = 12;

	spriteMap[wall14][x] = 4+29*12;
	spriteMap[wall14][y] = 4+6*12;
	spriteMap[wall14][sizex] = 12;
	spriteMap[wall14][sizey] = 12;

	spriteMap[wall15][x] = 4+30*12;
	spriteMap[wall15][y] = 4+6*12;
	spriteMap[wall15][sizex] = 12;
	spriteMap[wall15][sizey] = 12;

	spriteMap[wall16][x] = 4+31*12;
	spriteMap[wall16][y] = 4+6*12;
	spriteMap[wall16][sizex] = 12;
	spriteMap[wall16][sizey] = 12;
	
	spriteMap[wall17][x] = 4+0*12;
	spriteMap[wall17][y] = 4+7*12;
	spriteMap[wall17][sizex] = 12;
	spriteMap[wall17][sizey] = 12;

	spriteMap[wall18][x] = 4+1*12;
	spriteMap[wall18][y] = 4+7*12;
	spriteMap[wall18][sizex] = 12;
	spriteMap[wall18][sizey] = 12;

	spriteMap[wall19][x] = 4+2*12;
	spriteMap[wall19][y] = 4+7*12;
	spriteMap[wall19][sizex] = 12;
	spriteMap[wall19][sizey] = 12;

	spriteMap[wall20][x] = 4+3*12;
	spriteMap[wall20][y] = 4+7*12;
	spriteMap[wall20][sizex] = 12;
	spriteMap[wall20][sizey] = 12;

	spriteMap[wall21][x] = 4+4*12;
	spriteMap[wall21][y] = 4+7*12;
	spriteMap[wall21][sizex] = 12;
	spriteMap[wall21][sizey] = 12;

	spriteMap[wall22][x] = 4+5*12;
	spriteMap[wall22][y] = 4+7*12;
	spriteMap[wall22][sizex] = 12;
	spriteMap[wall22][sizey] = 12;

	spriteMap[wall23][x] = 4+6*12;
	spriteMap[wall23][y] = 4+7*12;
	spriteMap[wall23][sizex] = 12;
	spriteMap[wall23][sizey] = 12;

	spriteMap[wall24][x] = 4+7*12;
	spriteMap[wall24][y] = 4+7*12;
	spriteMap[wall24][sizex] = 12;
	spriteMap[wall24][sizey] = 12;

	spriteMap[wall25][x] = 4+8*12;
	spriteMap[wall25][y] = 4+7*12;
	spriteMap[wall25][sizex] = 12;
	spriteMap[wall25][sizey] = 12;

	spriteMap[wall26][x] = 4+9*12;
	spriteMap[wall26][y] = 4+7*12;
	spriteMap[wall26][sizex] = 12;
	spriteMap[wall26][sizey] = 12;

	spriteMap[wall27][x] = 4+10*12;
	spriteMap[wall27][y] = 4+7*12;
	spriteMap[wall27][sizex] = 12;
	spriteMap[wall27][sizey] = 12;

	spriteMap[wall28][x] = 4+11*12;
	spriteMap[wall28][y] = 4+7*12;
	spriteMap[wall28][sizex] = 12;
	spriteMap[wall28][sizey] = 12;

	spriteMap[wall29][x] = 4+12*12;
	spriteMap[wall29][y] = 4+7*12;
	spriteMap[wall29][sizex] = 12;
	spriteMap[wall29][sizey] = 12;

	spriteMap[wall30][x] = 4+13*12;
	spriteMap[wall30][y] = 4+7*12;
	spriteMap[wall30][sizex] = 12;
	spriteMap[wall30][sizey] = 12;

	spriteMap[wall31][x] = 4+14*12;
	spriteMap[wall31][y] = 4+7*12;
	spriteMap[wall31][sizex] = 12;
	spriteMap[wall31][sizey] = 12;

	spriteMap[wall32][x] = 4+15*12;
	spriteMap[wall32][y] = 4+7*12;
	spriteMap[wall32][sizex] = 12;
	spriteMap[wall32][sizey] = 12;

	spriteMap[wall33][x] = 4+16*12;
	spriteMap[wall33][y] = 4+7*12;
	spriteMap[wall33][sizex] = 12;
	spriteMap[wall33][sizey] = 12;

	spriteMap[wall34][x] = 4+17*12;
	spriteMap[wall34][y] = 4+7*12;
	spriteMap[wall34][sizex] = 12;
	spriteMap[wall34][sizey] = 12;

	spriteMap[wall35][x] = 4+18*12;
	spriteMap[wall35][y] = 4+7*12;
	spriteMap[wall35][sizex] = 12;
	spriteMap[wall35][sizey] = 12;

	spriteMap[wall36][x] = 4+19*12;
	spriteMap[wall36][y] = 4+7*12;
	spriteMap[wall36][sizex] = 12;
	spriteMap[wall36][sizey] = 12;

	spriteMap[wall37][x] = 4+20*12;
	spriteMap[wall37][y] = 4+7*12;
	spriteMap[wall37][sizex] = 12;
	spriteMap[wall37][sizey] = 12;

	spriteMap[wall38][x] = 4+21*12;
	spriteMap[wall38][y] = 4+7*12;
	spriteMap[wall38][sizex] = 12;
	spriteMap[wall38][sizey] = 12;

	spriteMap[wall39][x] = 4+22*12;
	spriteMap[wall39][y] = 4+7*12;
	spriteMap[wall39][sizex] = 12;
	spriteMap[wall39][sizey] = 12;

	spriteMap[wall40][x] = 4+23*12;
	spriteMap[wall40][y] = 4+7*12;
	spriteMap[wall40][sizex] = 12;
	spriteMap[wall40][sizey] = 12;

	spriteMap[wall41][x] = 4+24*12;
	spriteMap[wall41][y] = 4+7*12;
	spriteMap[wall41][sizex] = 12;
	spriteMap[wall41][sizey] = 12;

	spriteMap[wall42][x] = 4+25*12;
	spriteMap[wall42][y] = 4+7*12;
	spriteMap[wall42][sizex] = 12;
	spriteMap[wall42][sizey] = 12;

	spriteMap[wall43][x] = 4+26*12;
	spriteMap[wall43][y] = 4+7*12;
	spriteMap[wall43][sizex] = 12;
	spriteMap[wall43][sizey] = 12;

	spriteMap[wall44][x] = 4+27*12;
	spriteMap[wall44][y] = 4+7*12;
	spriteMap[wall44][sizex] = 12;
	spriteMap[wall44][sizey] = 12;

	spriteMap[wall45][x] = 4+28*12;
	spriteMap[wall45][y] = 4+7*12;
	spriteMap[wall45][sizex] = 12;
	spriteMap[wall45][sizey] = 12;

	spriteMap[wall46][x] = 4+29*12;
	spriteMap[wall46][y] = 4+7*12;
	spriteMap[wall46][sizex] = 12;
	spriteMap[wall46][sizey] = 12;
	
	// Map map content to objectTypes
	mapToSprite[0] = null;
	mapToSprite[1] = dot;
	mapToSprite[2] = pellet;
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
	mapToSprite[33] = door;
	mapToSprite[34] = null;
	
	// Map numbers to ObjectTypes
	numToSprite[0] = pacmanright;
	numToSprite[1] = pacmanright;
	numToSprite[2] = pacmanright;
	numToSprite[3] = pacmanright;
	numToSprite[4] = pacmanright;
	numToSprite[5] = pacmanright;
	numToSprite[6] = pacmanright;
	numToSprite[7] = pacmanright;
	numToSprite[8] = pacmanright;
	numToSprite[9] = pacmanright;
}

void Game::refresh(){
	
	SDL_RenderClear(renderer);
	
	// Draw all objects in field
	for(auto &i : field){
		i->draw();
		SDL_Rect dst = {i->pos.x+i->sprite.pos.x, i->pos.y+i->sprite.pos.y, spriteMap[(ObjectType)i->sprite.sprite][sizex],spriteMap[(ObjectType)i->sprite.sprite][sizey]};
		SDL_Rect src = {spriteMap[(ObjectType)i->sprite.sprite][x], spriteMap[(ObjectType)i->sprite.sprite][y], spriteMap[(ObjectType)i->sprite.sprite][sizex], spriteMap[(ObjectType)i->sprite.sprite][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw pacman
	pacman.draw();
	SDL_Rect dst = {pacman.pos.x+pacman.sprite.pos.x, pacman.pos.y+pacman.sprite.pos.y, spriteMap[(ObjectType)pacman.sprite.sprite][sizex],spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_Rect src = {spriteMap[(ObjectType)pacman.sprite.sprite][x], spriteMap[(ObjectType)pacman.sprite.sprite][y], spriteMap[(ObjectType)pacman.sprite.sprite][sizex], spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_RenderCopy(renderer, sheet, &src, &dst);
	
	drawScore();
	
	SDL_RenderPresent(renderer);
}

void Game::drawScore(){
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
		value = (score.score/digitSelector)%10;
		SDL_Rect dst = {13*24-digit*24, 31*12, 24,24};
		SDL_Rect src = {spriteMap[numToSprite[value]][x], spriteMap[numToSprite[value]][y], spriteMap[numToSprite[value]][sizex], spriteMap[numToSprite[value]][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
		digitSelector *= 10;
		digit++;
	}
}

uint32_t refreshTimer(uint32_t interval, void * param){
	((Game*)param)->refresh();
	return interval;
}

