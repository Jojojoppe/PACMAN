#include <Game.h>
#include <maps.h>

// StaticObjects
#include <Wall.h>
#include <Door.h>
#include <Tunnel.h>
#include <Dot.h>
#include <PowerPellet.h>
#include <Fruit.h>

#include <Pacman.h>
#include <InkyClyde.h>
#include <Pinky.h>
#include <Blinky.h>

#include <iostream>

void Game::main(){
	// Initialize window
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Programming 2: PACMAN",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  12*28+2, 12*31+1*24+4,
							  SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Load sprite sheet
	SDL_Surface *surf = SDL_LoadBMP("resources/sam_gfx.bmp");
	sheet = SDL_CreateTextureFromSurface(renderer, surf);
	if (sheet == nullptr) 
		std::cout << " error: " << SDL_GetError();
	loadSprites();
	
	score.game = (void*) this;
	resetGame();
	
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					case SDLK_LEFT:
						pacman.ndir = left;
						break;
					case SDLK_RIGHT:
						pacman.ndir = right;
						break;
					case SDLK_UP:
						pacman.ndir = up;
						break;
					case SDLK_DOWN:
						pacman.ndir = down;
						break;
					case SDLK_ESCAPE:
						quit= true; 
						break;
	            }
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
	
	int fruitnr = rand()%44;
	int fruitcnt = 0;
	int fruiti = 0;
	int fruitj = 0;
	
	// Create map
	for(int i=0; i<map.size(); i++)
		for(int j=0; j<map[i].size(); j++){
			// Wall
			if((map[i][j]>=10 && map[i][j]<=32) || (map[i][j]>=35 && map[i][j]<=38)){
				Wall * w = new Wall;
				w->pos.x = j*12-12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Door
			if(map[i][j]==33){
				Door * w = new Door;
				w->pos.x = j*12-12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Tunnel
			if(map[i][j]==34){
				Tunnel * w = new Tunnel;
				w->pos.x = j*12-12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// PowerPellet
			if(map[i][j]==2){
				PowerPellet * w = new PowerPellet;
				w->pos.x = j*12-12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			// Dot
			if(map[i][j]==1){
				Dot * w = new Dot;
				w->pos.x = j*12-12;
				w->pos.y = i*12;
				w->sprite.sprite = mapToSprite[map[i][j]];
				field.push_back(w);
			}
			
			// Empty spot for fruit
			if(map[i][j]==0){
				if(fruitcnt++ == fruitnr){
					fruiti = i;
					fruitj = j;
				}
			}
		}
	
	//Add Fruit
	Fruit * fruit = new Fruit();
	fruit->pos.y = fruiti*12;
	fruit->pos.x = fruitj*12-12;
	fruit->sprite.pos.x = -6;
	fruit->sprite.pos.y = -6;
	fruit->sprite.sprite = null;
	field.push_back(fruit);

	// Add pacman
	pacman.pos.y = 23*12;
	pacman.pos.x = 14*12;
	pacman.dir = left;
	pacman.ndir = left;
	pacman.sprite.sprite = PacmanEatRight1;
	pacman.sprite.pos.x = -6;
	pacman.sprite.pos.y = -6;
	pacman.speed = 5;
	pacman.game = (void *) this;
	
	// Add inky
	InkyClyde * inky = new InkyClyde((void*)this);
	inky->spritebase = InkyUp1;
	field.push_back(inky);
	
	// Add clyde
	InkyClyde * clyde = new InkyClyde((void*)this);
	clyde->spritebase = ClydeUp1;
	field.push_back(clyde);
	
	// Add Pinky
	Pinky * pinky = new Pinky((void*)this);
	pinky->spritebase = PinkyUp1;
	field.push_back(pinky);

	// Add Blinky
	Blinky * blinky = new Blinky((void*)this);
	blinky->spritebase = BlinkyUp1;
	field.push_back(blinky);
	
	refresh();
	timer = SDL_AddTimer(50, refreshTimer, (void *)this);
	
}

void Game::loadSprites(){
	
	//------------
	// Ghosts
	//------------

	//PinkyRight1
	spriteMap[PinkyRight1][x] = 3 + 0*24;
	spriteMap[PinkyRight1][y] = 5 + 9*24;
	spriteMap[PinkyRight1][sizex] = 24;
	spriteMap[PinkyRight1][sizey] = 24;

	//PinkyRight2
	spriteMap[PinkyRight2][x] = 3 + 1*24;
	spriteMap[PinkyRight2][y] = 5 + 9*24;
	spriteMap[PinkyRight2][sizex] = 24;
	spriteMap[PinkyRight2][sizey] = 24;

	//PinkyDown1
	spriteMap[PinkyDown1][x] = 3 + 2*24;
	spriteMap[PinkyDown1][y] = 4 + 9*24;
	spriteMap[PinkyDown1][sizex] = 24;
	spriteMap[PinkyDown1][sizey] = 24;

	//PinkyDown2
	spriteMap[PinkyDown2][x] = 3 + 3*24;
	spriteMap[PinkyDown2][y] = 4 + 9*24;
	spriteMap[PinkyDown2][sizex] = 24;
	spriteMap[PinkyDown2][sizey] = 24;

	//PinkyLeft1
	spriteMap[PinkyLeft1][x] = 3 + 4*24;
	spriteMap[PinkyLeft1][y] = 4 + 9*24;
	spriteMap[PinkyLeft1][sizex] = 24;
	spriteMap[PinkyLeft1][sizey] = 24;

	//PinkyLeft2
	spriteMap[PinkyLeft2][x] = 3 + 5*24;
	spriteMap[PinkyLeft2][y] = 4 + 9*24;
	spriteMap[PinkyLeft2][sizex] = 24;
	spriteMap[PinkyLeft2][sizey] = 24;

	//PinkyUp1
	spriteMap[PinkyUp1][x] = 3 + 6*24;
	spriteMap[PinkyUp1][y] = 4 + 9*24;
	spriteMap[PinkyUp1][sizex] = 24;
	spriteMap[PinkyUp1][sizey] = 24;

	//PinkyUp2
	spriteMap[PinkyUp2][x] = 3 + 7*24;
	spriteMap[PinkyUp2][y] = 4 + 9*24;
	spriteMap[PinkyUp2][sizex] = 24;
	spriteMap[PinkyUp2][sizey] = 24;
	//----------------------------------------------------
	//InkyRight1
	spriteMap[InkyRight1][x] = 3 + 8*24;
	spriteMap[InkyRight1][y] = 4 + 9*24;
	spriteMap[InkyRight1][sizex] = 24;
	spriteMap[InkyRight1][sizey] = 24;

	//InkyRight2
	spriteMap[InkyRight2][x] = 3 + 9*24;
	spriteMap[InkyRight2][y] = 4 + 9*24;
	spriteMap[InkyRight2][sizex] = 24;
	spriteMap[InkyRight2][sizey] = 24;

	//InkyDown1
	spriteMap[InkyDown1][x] = 3 + 10*24;
	spriteMap[InkyDown1][y] = 4 + 9*24;
	spriteMap[InkyDown1][sizex] = 24;
	spriteMap[InkyDown1][sizey] = 24;

	//InkyDown2
	spriteMap[InkyDown2][x] = 3 + 11*24;
	spriteMap[InkyDown2][y] = 4 + 9*24;
	spriteMap[InkyDown2][sizex] = 24;
	spriteMap[InkyDown2][sizey] = 24;

	//InkyLeft1
	spriteMap[InkyLeft1][x] = 3 + 12*24;
	spriteMap[InkyLeft1][y] = 4 + 9*24;
	spriteMap[InkyLeft1][sizex] = 24;
	spriteMap[InkyLeft1][sizey] = 24;

	//InkyLeft2
	spriteMap[InkyLeft2][x] = 3 + 13*24;
	spriteMap[InkyLeft2][y] = 4 + 9*24;
	spriteMap[InkyLeft2][sizex] = 24;
	spriteMap[InkyLeft2][sizey] = 24;

	//InkyUp1
	spriteMap[InkyUp1][x] = 3 + 14*24;
	spriteMap[InkyUp1][y] = 4 + 9*24;
	spriteMap[InkyUp1][sizex] = 24;
	spriteMap[InkyUp1][sizey] = 24;

	//InkyUp2
	spriteMap[InkyUp2][x] = 3 + 15*24;
	spriteMap[InkyUp2][y] = 4 + 9*24;
	spriteMap[InkyUp2][sizex] = 24;
	spriteMap[InkyUp2][sizey] = 24;
	//---------------------------------------------

	//ClydeRight1
	spriteMap[ClydeRight1][x] = 3 + 0*24;
	spriteMap[ClydeRight1][y] = 4 + 10*24;
	spriteMap[ClydeRight1][sizex] = 24;
	spriteMap[ClydeRight1][sizey] = 24;

	//PClydeRight2
	spriteMap[ClydeRight2][x] = 3 + 1*24;
	spriteMap[ClydeRight2][y] = 4 + 10*24;
	spriteMap[ClydeRight2][sizex] = 24;
	spriteMap[ClydeRight2][sizey] = 24;

	//ClydeDown1
	spriteMap[ClydeDown1][x] = 3 + 2*24;
	spriteMap[ClydeDown1][y] = 4 + 10*24;
	spriteMap[ClydeDown1][sizex] = 24;
	spriteMap[ClydeDown1][sizey] = 24;

	//ClydeDown2
	spriteMap[ClydeDown2][x] = 3 + 3*24;
	spriteMap[ClydeDown2][y] = 4 + 10*24;
	spriteMap[ClydeDown2][sizex] = 24;
	spriteMap[ClydeDown2][sizey] = 24;

	//ClydeLeft1
	spriteMap[ClydeLeft1][x] = 3 + 4*24;
	spriteMap[ClydeLeft1][y] = 4 + 10*24;
	spriteMap[ClydeLeft1][sizex] = 24;
	spriteMap[ClydeLeft1][sizey] = 24;

	//ClydeLeft2
	spriteMap[ClydeLeft2][x] = 3 + 5*24;
	spriteMap[ClydeLeft2][y] = 4 + 10*24;
	spriteMap[ClydeLeft2][sizex] = 24;
	spriteMap[ClydeLeft2][sizey] = 24;

	//ClydeUp1
	spriteMap[ClydeUp1][x] = 3 + 6*24;
	spriteMap[ClydeUp1][y] = 4 + 10*24;
	spriteMap[ClydeUp1][sizex] = 24;
	spriteMap[ClydeUp1][sizey] = 24;

	//ClydeUp2
	spriteMap[ClydeUp2][x] = 3 + 7*24;
	spriteMap[ClydeUp2][y] = 4 + 10*24;
	spriteMap[ClydeUp2][sizex] = 24;
	spriteMap[ClydeUp2][sizey] = 24;
	//------------------------------------------------------
	//BlinkyRight1
	spriteMap[BlinkyRight1][x] = 3 + 0*24;
	spriteMap[BlinkyRight1][y] = 4 + 7*24;
	spriteMap[BlinkyRight1][sizex] = 24;
	spriteMap[BlinkyRight1][sizey] = 24;

	//PBlinkyRight2
	spriteMap[BlinkyRight2][x] = 3 + 1*24;
	spriteMap[BlinkyRight2][y] = 4 + 7*24;
	spriteMap[BlinkyRight2][sizex] = 24;
	spriteMap[BlinkyRight2][sizey] = 24;

	//BlinkyDown1
	spriteMap[BlinkyDown1][x] = 3 + 2*24;
	spriteMap[BlinkyDown1][y] = 4 + 7*24;
	spriteMap[BlinkyDown1][sizex] = 24;
	spriteMap[BlinkyDown1][sizey] = 24;

	//BlinkyDown2
	spriteMap[BlinkyDown2][x] = 3 + 3*24;
	spriteMap[BlinkyDown2][y] = 4 + 7*24;
	spriteMap[BlinkyDown2][sizex] = 24;
	spriteMap[BlinkyDown2][sizey] = 24;

	//BlinkyLeft1
	spriteMap[BlinkyLeft1][x] = 3 + 4*24;
	spriteMap[BlinkyLeft1][y] = 4 + 7*24;
	spriteMap[BlinkyLeft1][sizex] = 24;
	spriteMap[BlinkyLeft1][sizey] = 24;

	//BlinkyLeft2
	spriteMap[BlinkyLeft2][x] = 3 + 5*24;
	spriteMap[BlinkyLeft2][y] = 4 + 7*24;
	spriteMap[BlinkyLeft2][sizex] = 24;
	spriteMap[BlinkyLeft2][sizey] = 24;

	//BlinkyUp1
	spriteMap[BlinkyUp1][x] = 3 + 6*24;
	spriteMap[BlinkyUp1][y] = 4 + 7*24;
	spriteMap[BlinkyUp1][sizex] = 24;
	spriteMap[BlinkyUp1][sizey] = 24;

	//BlinkyUp2
	spriteMap[BlinkyUp2][x] = 3 + 7*24;
	spriteMap[BlinkyUp2][y] = 4 + 7*24;
	spriteMap[BlinkyUp2][sizex] = 24;
	spriteMap[BlinkyUp2][sizey] = 24;
	//-----------------------------------------------------

	//GhostDead1
	spriteMap[GhostDead1][x] = 3 + 12*24;
	spriteMap[GhostDead1][y] = 4 + 6*24;
	spriteMap[GhostDead1][sizex] = 24;
	spriteMap[GhostDead1][sizey] = 24;

	//GhostDead2
	spriteMap[GhostDead2][x] = 3 + 13*24;
	spriteMap[GhostDead2][y] = 4 + 6*24;
	spriteMap[GhostDead2][sizex] = 24;
	spriteMap[GhostDead2][sizey] = 24;
	 
	//GhostAlmostDead1
	spriteMap[GhostAlmostDead1][x] = 3 + 4*24;
	spriteMap[GhostAlmostDead1][y] = 4 + 11*24;
	spriteMap[GhostAlmostDead1][sizex] = 24;
	spriteMap[GhostAlmostDead1][sizey] = 24;

	//GhostAlmostDead2
	spriteMap[GhostAlmostDead2][x] = 3 + 5*24;
	spriteMap[GhostAlmostDead2][y] = 4 + 11*24;
	spriteMap[GhostAlmostDead2][sizex] = 24;
	spriteMap[GhostAlmostDead2][sizey] = 24;
	
	//eyesUp
	spriteMap[eyesUp][x] = 4 + 14*24;
	spriteMap[eyesUp][y] = 4 + 10*24;
	spriteMap[eyesUp][sizex] = 24;
	spriteMap[eyesUp][sizey] = 24;

	//eyesDown
	spriteMap[eyesDown][x] = 4 + 11*24;
	spriteMap[eyesDown][y] = 4 + 10*24;
	spriteMap[eyesDown][sizex] = 24;
	spriteMap[eyesDown][sizey] = 24;

	//eyesLeft
	spriteMap[eyesLeft][x] = 4 + 12*24;
	spriteMap[eyesLeft][y] = 4 + 10*24;
	spriteMap[eyesLeft][sizex] = 24;
	spriteMap[eyesLeft][sizey] = 24;

	//eyesRight
	spriteMap[eyesRight][x] = 4 + 9*24;
	spriteMap[eyesRight][y] = 4 + 10*24;
	spriteMap[eyesRight][sizex] = 24;
	spriteMap[eyesRight][sizey] = 24;

	//-----------
	//Scores
	//-----------
	//Score200
	spriteMap[Score200][x] = 4 + 8*24;
	spriteMap[Score200][y] = 5 + 7*24;
	spriteMap[Score200][sizex] = 24;
	spriteMap[Score200][sizey] = 24;

	//Score400
	spriteMap[Score400][x] = 4 + 9*24;
	spriteMap[Score400][y] = 5 + 7*24;
	spriteMap[Score400][sizex] = 24;
	spriteMap[Score400][sizey] = 24;

	//Score800
	spriteMap[Score800][x] = 4 + 10*24;
	spriteMap[Score800][y] = 5 + 7*24;
	spriteMap[Score800][sizex] = 24;
	spriteMap[Score800][sizey] = 24;

	//Score1600
	spriteMap[Score1600][x] = 4 + 11*24;
	spriteMap[Score1600][y] = 5 + 7*24;
	spriteMap[Score1600][sizex] = 24;
	spriteMap[Score1600][sizey] = 24;
	
	//fruitCherry
	spriteMap[fruitCherry][x] = 4 + 0*24;
	spriteMap[fruitCherry][y] = 4 + 5*24;
	spriteMap[fruitCherry][sizex] = 24;
	spriteMap[fruitCherry][sizey] = 24;

	//fruitStrawberry
	spriteMap[fruitStrawberry][x] = 4 + 1*24;
	spriteMap[fruitStrawberry][y] = 4 + 5*24;
	spriteMap[fruitStrawberry][sizex] = 24;
	spriteMap[fruitStrawberry][sizey] = 24;

	//fruitOrange
	spriteMap[fruitOrange][x] = 4 + 2*24;
	spriteMap[fruitOrange][y] = 4 + 5*24;
	spriteMap[fruitOrange][sizex] = 24;
	spriteMap[fruitOrange][sizey] = 24;

	//fruitLemon
	spriteMap[fruitLemon][x] = 4 + 3*24;
	spriteMap[fruitLemon][y] = 4 + 5*24;
	spriteMap[fruitLemon][sizex] = 24;
	spriteMap[fruitLemon][sizey] = 24;

	//fruitApple
	spriteMap[fruitApple][x] = 4 + 4*24;
	spriteMap[fruitApple][y] = 4 + 5*24;
	spriteMap[fruitApple][sizex] = 24;
	spriteMap[fruitApple][sizey] = 24;

	//fruitGrapes
	spriteMap[fruitGrapes][x] = 4 + 5*24;
	spriteMap[fruitGrapes][y] = 4 + 5*24;
	spriteMap[fruitGrapes][sizex] = 24;
	spriteMap[fruitGrapes][sizey] = 24;
	
	
	//----------------------
	//Pacman eating
	//----------------------
	//PacmanEatFull
	spriteMap[PacmanEatFull][x] = 4 + 0*24;
	spriteMap[PacmanEatFull][y] = 4 + 8*24;
	spriteMap[PacmanEatFull][sizex] = 24;
	spriteMap[PacmanEatFull][sizey] = 24;

	//PacmanEatRight1
	spriteMap[PacmanEatRight1][x] = 4 + 12*24;
	spriteMap[PacmanEatRight1][y] = 4 + 7*24;
	spriteMap[PacmanEatRight1][sizex] = 24;
	spriteMap[PacmanEatRight1][sizey] = 24;

	//PacmanEatRight2
	spriteMap[PacmanEatRight2][x] = 4 + 14*24;
	spriteMap[PacmanEatRight2][y] = 4 + 7*24;
	spriteMap[PacmanEatRight2][sizex] = 24;
	spriteMap[PacmanEatRight2][sizey] = 24;

	//PacmanEatDown1
	spriteMap[PacmanEatDown1][x] = 4 + 13*24;
	spriteMap[PacmanEatDown1][y] = 4 + 7*24;
	spriteMap[PacmanEatDown1][sizex] = 24;
	spriteMap[PacmanEatDown1][sizey] = 24;

	//PacmanEatDown2
	spriteMap[PacmanEatDown2][x] = 4 + 15*24;
	spriteMap[PacmanEatDown2][y] = 4 + 7*24;
	spriteMap[PacmanEatDown2][sizex] = 24;
	spriteMap[PacmanEatDown2][sizey] = 24;

	//PacmanEatLeft1
	spriteMap[PacmanEatLeft1][x] = 4 + 0*24;
	spriteMap[PacmanEatLeft1][y] = 4 + 11*24;
	spriteMap[PacmanEatLeft1][sizex] = 24;
	spriteMap[PacmanEatLeft1][sizey] = 24;

	//PacmanEatLeft2
	spriteMap[PacmanEatLeft2][x] = 4 + 2*24;
	spriteMap[PacmanEatLeft2][y] = 4 + 11*24;
	spriteMap[PacmanEatLeft2][sizex] = 24;
	spriteMap[PacmanEatLeft2][sizey] = 24;

	//PacmanEatUp1
	spriteMap[PacmanEatUp1][x] = 4 + 1*24;
	spriteMap[PacmanEatUp1][y] = 4 + 11*24;
	spriteMap[PacmanEatUp1][sizex] = 24;
	spriteMap[PacmanEatUp1][sizey] = 24;

	//PacmanEatUp2
	spriteMap[PacmanEatUp2][x] = 4 + 3*24;
	spriteMap[PacmanEatUp2][y] = 4 + 11*24;
	spriteMap[PacmanEatUp2][sizex] = 24;
	spriteMap[PacmanEatUp2][sizey] = 24;

	//---------------------------
	//PacmanDying
	//---------------------------
	//PacmanDyingS1
	spriteMap[PacmanDyingS1][x] = 4 + 1*24;
	spriteMap[PacmanDyingS1][y] = 4 + 11*24;
	spriteMap[PacmanDyingS1][sizex] = 24;
	spriteMap[PacmanDyingS1][sizey] = 24;

	//PacmanDyingS2
	spriteMap[PacmanDyingS2][x] = 4 + 4*24;
	spriteMap[PacmanDyingS2][y] = 4 + 8*24;
	spriteMap[PacmanDyingS2][sizex] = 24;
	spriteMap[PacmanDyingS2][sizey] = 24;

	//PacmanDyingS3
	spriteMap[PacmanDyingS3][x] = 4 + 5*24;
	spriteMap[PacmanDyingS3][y] = 4 + 8*24;
	spriteMap[PacmanDyingS3][sizex] = 24;
	spriteMap[PacmanDyingS3][sizey] = 24;

	//PacmanDyingS4
	spriteMap[PacmanDyingS4][x] = 4 + 6*24;
	spriteMap[PacmanDyingS4][y] = 4 + 8*24;
	spriteMap[PacmanDyingS4][sizex] = 24;
	spriteMap[PacmanDyingS4][sizey] = 24;

	//PacmanDyingS5
	spriteMap[PacmanDyingS5][x] = 4 + 7*24;
	spriteMap[PacmanDyingS5][y] = 4 + 8*24;
	spriteMap[PacmanDyingS5][sizex] = 24;
	spriteMap[PacmanDyingS5][sizey] = 24;

	//PacmanDyingS6
	spriteMap[PacmanDyingS6][x] = 4 + 8*24;
	spriteMap[PacmanDyingS6][y] = 4 + 8*24;
	spriteMap[PacmanDyingS6][sizex] = 24;
	spriteMap[PacmanDyingS6][sizey] = 24;

	//PacmanDyingS7
	spriteMap[PacmanDyingS7][x] = 4 + 9*24;
	spriteMap[PacmanDyingS7][y] = 4 + 8*24;
	spriteMap[PacmanDyingS7][sizex] = 24;
	spriteMap[PacmanDyingS7][sizey] = 24;

	//PacmanDyingS8
	spriteMap[PacmanDyingS8][x] = 4 + 10*24;
	spriteMap[PacmanDyingS8][y] = 4 + 8*24;
	spriteMap[PacmanDyingS8][sizex] = 24;
	spriteMap[PacmanDyingS8][sizey] = 24;

	//PacmanDyingS9
	spriteMap[PacmanDyingS9][x] = 4 + 11*24;
	spriteMap[PacmanDyingS9][y] = 4 + 8*24;
	spriteMap[PacmanDyingS9][sizex] = 24;
	spriteMap[PacmanDyingS9][sizey] = 24;

	//PacmanDyingS10
	spriteMap[PacmanDyingS10][x] = 4 + 12*24;
	spriteMap[PacmanDyingS10][y] = 4 + 8*24;
	spriteMap[PacmanDyingS10][sizex] = 24;
	spriteMap[PacmanDyingS10][sizey] = 24;

	//PacmanDyingS11
	spriteMap[PacmanDyingS11][x] = 4 + 13*24;
	spriteMap[PacmanDyingS11][y] = 4 + 8*24;
	spriteMap[PacmanDyingS11][sizex] = 24;
	spriteMap[PacmanDyingS11][sizey] = 24;

	//PacmanDyingS12
	spriteMap[PacmanDyingS12][x] = 4 + 14*24;
	spriteMap[PacmanDyingS12][y] = 4 + 8*24;
	spriteMap[PacmanDyingS12][sizex] = 24;
	spriteMap[PacmanDyingS12][sizey] = 24;
	
	// Specials
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
	spriteMap[wall1][y] = 5+6*12;
	spriteMap[wall1][sizex] = 12;
	spriteMap[wall1][sizey] = 12;
	
	spriteMap[wall2][x] = 4+17*12;
	spriteMap[wall2][y] = 5+6*12;
	spriteMap[wall2][sizex] = 12;
	spriteMap[wall2][sizey] = 12;
	
	spriteMap[wall3][x] = 4+18*12;
	spriteMap[wall3][y] = 5+6*12;
	spriteMap[wall3][sizex] = 12;
	spriteMap[wall3][sizey] = 12;
	
	spriteMap[wall4][x] = 4+19*12;
	spriteMap[wall4][y] = 5+6*12;
	spriteMap[wall4][sizex] = 12;
	spriteMap[wall4][sizey] = 12;
	
	spriteMap[wall5][x] = 4+20*12;
	spriteMap[wall5][y] = 5+6*12;
	spriteMap[wall5][sizex] = 12;
	spriteMap[wall5][sizey] = 12;

	spriteMap[wall6][x] = 4+21*12;
	spriteMap[wall6][y] = 5+6*12;
	spriteMap[wall6][sizex] = 12;
	spriteMap[wall6][sizey] = 12;

	spriteMap[wall7][x] = 4+22*12;
	spriteMap[wall7][y] = 5+6*12;
	spriteMap[wall7][sizex] = 12;
	spriteMap[wall7][sizey] = 12;

	spriteMap[wall8][x] = 4+23*12;
	spriteMap[wall8][y] = 5+6*12;
	spriteMap[wall8][sizex] = 12;
	spriteMap[wall8][sizey] = 12;

	spriteMap[wall9][x] = 4+24*12;
	spriteMap[wall9][y] = 5+6*12;
	spriteMap[wall9][sizex] = 12;
	spriteMap[wall9][sizey] = 12;

	spriteMap[wall10][x] = 4+25*12;
	spriteMap[wall10][y] = 5+6*12;
	spriteMap[wall10][sizex] = 12;
	spriteMap[wall10][sizey] = 12;

	spriteMap[wall11][x] = 4+26*12;
	spriteMap[wall11][y] = 5+6*12;
	spriteMap[wall11][sizex] = 12;
	spriteMap[wall11][sizey] = 12;

	spriteMap[wall12][x] = 4+27*12;
	spriteMap[wall12][y] = 5+6*12;
	spriteMap[wall12][sizex] = 12;
	spriteMap[wall12][sizey] = 12;

	spriteMap[wall13][x] = 4+28*12;
	spriteMap[wall13][y] = 5+6*12;
	spriteMap[wall13][sizex] = 12;
	spriteMap[wall13][sizey] = 12;

	spriteMap[wall14][x] = 4+29*12;
	spriteMap[wall14][y] = 5+6*12;
	spriteMap[wall14][sizex] = 12;
	spriteMap[wall14][sizey] = 12;

	spriteMap[wall15][x] = 4+30*12;
	spriteMap[wall15][y] = 5+6*12;
	spriteMap[wall15][sizex] = 12;
	spriteMap[wall15][sizey] = 12;

	spriteMap[wall16][x] = 4+31*12;
	spriteMap[wall16][y] = 5+6*12;
	spriteMap[wall16][sizex] = 12;
	spriteMap[wall16][sizey] = 12;
	
	spriteMap[wall17][x] = 4+0*12;
	spriteMap[wall17][y] = 5+7*12;
	spriteMap[wall17][sizex] = 12;
	spriteMap[wall17][sizey] = 12;

	spriteMap[wall18][x] = 4+1*12;
	spriteMap[wall18][y] = 5+7*12;
	spriteMap[wall18][sizex] = 12;
	spriteMap[wall18][sizey] = 12;

	spriteMap[wall19][x] = 4+2*12;
	spriteMap[wall19][y] = 5+7*12;
	spriteMap[wall19][sizex] = 12;
	spriteMap[wall19][sizey] = 12;

	spriteMap[wall20][x] = 4+3*12;
	spriteMap[wall20][y] = 5+7*12;
	spriteMap[wall20][sizex] = 12;
	spriteMap[wall20][sizey] = 12;

	spriteMap[wall21][x] = 4+4*12;
	spriteMap[wall21][y] = 5+7*12;
	spriteMap[wall21][sizex] = 12;
	spriteMap[wall21][sizey] = 12;

	spriteMap[wall22][x] = 4+5*12;
	spriteMap[wall22][y] = 5+7*12;
	spriteMap[wall22][sizex] = 12;
	spriteMap[wall22][sizey] = 12;

	spriteMap[wall23][x] = 4+6*12;
	spriteMap[wall23][y] = 5+7*12;
	spriteMap[wall23][sizex] = 12;
	spriteMap[wall23][sizey] = 12;

	spriteMap[wall24][x] = 4+7*12;
	spriteMap[wall24][y] = 5+7*12;
	spriteMap[wall24][sizex] = 12;
	spriteMap[wall24][sizey] = 12;

	spriteMap[wall25][x] = 4+8*12;
	spriteMap[wall25][y] = 5+7*12;
	spriteMap[wall25][sizex] = 12;
	spriteMap[wall25][sizey] = 12;

	spriteMap[wall26][x] = 4+9*12;
	spriteMap[wall26][y] = 5+7*12;
	spriteMap[wall26][sizex] = 12;
	spriteMap[wall26][sizey] = 12;

	spriteMap[wall27][x] = 4+10*12;
	spriteMap[wall27][y] = 5+7*12;
	spriteMap[wall27][sizex] = 12;
	spriteMap[wall27][sizey] = 12;

	spriteMap[wall28][x] = 4+11*12;
	spriteMap[wall28][y] = 5+7*12;
	spriteMap[wall28][sizex] = 12;
	spriteMap[wall28][sizey] = 12;

	spriteMap[wall29][x] = 4+12*12;
	spriteMap[wall29][y] = 5+7*12;
	spriteMap[wall29][sizex] = 12;
	spriteMap[wall29][sizey] = 12;

	spriteMap[wall30][x] = 4+13*12;
	spriteMap[wall30][y] = 5+7*12;
	spriteMap[wall30][sizex] = 12;
	spriteMap[wall30][sizey] = 12;

	spriteMap[wall31][x] = 4+14*12;
	spriteMap[wall31][y] = 5+7*12;
	spriteMap[wall31][sizex] = 12;
	spriteMap[wall31][sizey] = 12;

	spriteMap[wall32][x] = 4+15*12;
	spriteMap[wall32][y] = 5+7*12;
	spriteMap[wall32][sizex] = 12;
	spriteMap[wall32][sizey] = 12;

	spriteMap[wall33][x] = 4+16*12;
	spriteMap[wall33][y] = 5+7*12;
	spriteMap[wall33][sizex] = 12;
	spriteMap[wall33][sizey] = 12;

	spriteMap[wall34][x] = 4+17*12;
	spriteMap[wall34][y] = 5+7*12;
	spriteMap[wall34][sizex] = 12;
	spriteMap[wall34][sizey] = 12;

	spriteMap[wall35][x] = 4+18*12;
	spriteMap[wall35][y] = 5+7*12;
	spriteMap[wall35][sizex] = 12;
	spriteMap[wall35][sizey] = 12;

	spriteMap[wall36][x] = 4+19*12;
	spriteMap[wall36][y] = 5+7*12;
	spriteMap[wall36][sizex] = 12;
	spriteMap[wall36][sizey] = 12;

	spriteMap[wall37][x] = 4+20*12;
	spriteMap[wall37][y] = 5+7*12;
	spriteMap[wall37][sizex] = 12;
	spriteMap[wall37][sizey] = 12;

	spriteMap[wall38][x] = 4+21*12;
	spriteMap[wall38][y] = 5+7*12;
	spriteMap[wall38][sizex] = 12;
	spriteMap[wall38][sizey] = 12;

	spriteMap[wall39][x] = 4+22*12;
	spriteMap[wall39][y] = 5+7*12;
	spriteMap[wall39][sizex] = 12;
	spriteMap[wall39][sizey] = 12;

	spriteMap[wall40][x] = 4+23*12;
	spriteMap[wall40][y] = 5+7*12;
	spriteMap[wall40][sizex] = 12;
	spriteMap[wall40][sizey] = 12;

	spriteMap[wall41][x] = 4+24*12;
	spriteMap[wall41][y] = 5+7*12;
	spriteMap[wall41][sizex] = 12;
	spriteMap[wall41][sizey] = 12;

	spriteMap[wall42][x] = 4+25*12;
	spriteMap[wall42][y] = 5+7*12;
	spriteMap[wall42][sizex] = 12;
	spriteMap[wall42][sizey] = 12;

	spriteMap[wall43][x] = 4+26*12;
	spriteMap[wall43][y] = 5+7*12;
	spriteMap[wall43][sizex] = 12;
	spriteMap[wall43][sizey] = 12;

	spriteMap[wall44][x] = 4+27*12;
	spriteMap[wall44][y] = 5+7*12;
	spriteMap[wall44][sizex] = 12;
	spriteMap[wall44][sizey] = 12;

	spriteMap[wall45][x] = 4+28*12;
	spriteMap[wall45][y] = 5+7*12;
	spriteMap[wall45][sizex] = 12;
	spriteMap[wall45][sizey] = 12;

	spriteMap[wall46][x] = 4+29*12;
	spriteMap[wall46][y] = 5+7*12;
	spriteMap[wall46][sizex] = 12;
	spriteMap[wall46][sizey] = 12;
	
	// Black background
	spriteMap[null][x] = 4+30*12;
	spriteMap[null][y] = 5+7*12;
	spriteMap[null][sizex] = 12;
	spriteMap[null][sizey] = 12;
	
	// Numbers
	spriteMap[num0][x] = 4+0*12;
	spriteMap[num0][y] = 5;
	spriteMap[num0][sizex] = 12;
	spriteMap[num0][sizey] = 12;

	spriteMap[num1][x] = 4+1*12;
	spriteMap[num1][y] = 5;
	spriteMap[num1][sizex] = 12;
	spriteMap[num1][sizey] = 12;

	spriteMap[num2][x] = 4+2*12;
	spriteMap[num2][y] = 5;
	spriteMap[num2][sizex] = 12;
	spriteMap[num2][sizey] = 12;

	spriteMap[num3][x] = 4+3*12;
	spriteMap[num3][y] = 5;
	spriteMap[num3][sizex] = 12;
	spriteMap[num3][sizey] = 12;

	spriteMap[num4][x] = 4+4*12;
	spriteMap[num4][y] = 5;
	spriteMap[num4][sizex] = 12;
	spriteMap[num4][sizey] = 12;

	spriteMap[num5][x] = 4+5*12;
	spriteMap[num5][y] = 5;
	spriteMap[num5][sizex] = 12;
	spriteMap[num5][sizey] = 12;

	spriteMap[num6][x] = 4+6*12;
	spriteMap[num6][y] = 5;
	spriteMap[num6][sizex] = 12;
	spriteMap[num6][sizey] = 12;

	spriteMap[num7][x] = 4+7*12;
	spriteMap[num7][y] = 5;
	spriteMap[num7][sizex] = 12;
	spriteMap[num7][sizey] = 12;

	spriteMap[num8][x] = 4+8*12;
	spriteMap[num8][y] = 5;
	spriteMap[num8][sizex] = 12;
	spriteMap[num8][sizey] = 12;
	
	spriteMap[num9][x] = 4+9*12;
	spriteMap[num9][y] = 5;
	spriteMap[num9][sizex] = 12;
	spriteMap[num9][sizey] = 12;
	
	spriteMap[null_empty][x] = 0;
	spriteMap[null_empty][y] = 0;
	spriteMap[null_empty][sizex] = 0;
	spriteMap[null_empty][sizey] = 0;
	
	// Map map content to objectTypes
	mapToSprite[0] = null;
	mapToSprite[1] = dot;
	mapToSprite[2] = pellet;
	mapToSprite[10] = wall2;
	mapToSprite[11] = wall11;
	mapToSprite[12] = wall1;
	mapToSprite[13] = wall3;
	mapToSprite[14] = wall4;
	mapToSprite[15] = wall13;
	mapToSprite[16] = wall44;
	mapToSprite[17] = wall43;
	mapToSprite[18] = wall25;
	mapToSprite[19] = wall26;
	mapToSprite[20] = wall21;
	mapToSprite[21] = wall15;
	mapToSprite[22] = wall28;
	mapToSprite[23] = wall27;
	mapToSprite[24] = wall23;
	mapToSprite[25] = wall24;
	mapToSprite[26] = wall6;
	mapToSprite[27] = wall5;
	mapToSprite[28] = null;
	mapToSprite[29] = wall8;
	mapToSprite[30] = wall10;
	mapToSprite[31] = wall9;
	mapToSprite[32] = wall7;	
	mapToSprite[33] = door;
	mapToSprite[34] = null;
	mapToSprite[35] = wall37;
	mapToSprite[36] = wall38;
	mapToSprite[37] = wall36;
	mapToSprite[38] = wall35;
	
	// Map numbers to ObjectTypes
	numToSprite[0] = num0;
	numToSprite[1] = num1;
	numToSprite[2] = num2;
	numToSprite[3] = num3;
	numToSprite[4] = num4;
	numToSprite[5] = num5;
	numToSprite[6] = num6;
	numToSprite[7] = num7;
	numToSprite[8] = num8;
	numToSprite[9] = num9;
}

void Game::refresh(){
	
	SDL_RenderClear(renderer);
	
	// Create black/darkgrey background
	SDL_Rect dst = {0, 0, 12*28+2, 12*31+1*24+4};
	SDL_Rect src = {spriteMap[null][x], spriteMap[null][y], spriteMap[null][sizex], spriteMap[null][sizey]};
	SDL_RenderCopy(renderer, sheet, &src, &dst);
	
	// Draw all objects in field
	for(auto &i : field){
		i->draw();
		SDL_Rect dst = {i->pos.x+i->sprite.pos.x, i->pos.y+i->sprite.pos.y, spriteMap[(ObjectType)i->sprite.sprite][sizex],spriteMap[(ObjectType)i->sprite.sprite][sizey]};
		SDL_Rect src = {spriteMap[(ObjectType)i->sprite.sprite][x], spriteMap[(ObjectType)i->sprite.sprite][y], spriteMap[(ObjectType)i->sprite.sprite][sizex], spriteMap[(ObjectType)i->sprite.sprite][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw pacman
	pacman.draw();
	dst = {pacman.pos.x+pacman.sprite.pos.x, pacman.pos.y+pacman.sprite.pos.y, spriteMap[(ObjectType)pacman.sprite.sprite][sizex],spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	src = {spriteMap[(ObjectType)pacman.sprite.sprite][x], spriteMap[(ObjectType)pacman.sprite.sprite][y], spriteMap[(ObjectType)pacman.sprite.sprite][sizex], spriteMap[(ObjectType)pacman.sprite.sprite][sizey]};
	SDL_RenderCopy(renderer, sheet, &src, &dst);
	
	// Move pacman
	pacman.move();
	pacman.checkCollision();
	
	// Move ghosts
	for(auto &i : field){
		if(dynamic_cast<Ghost*>(i)!=NULL)
			((Ghost*)i)->move();
	}
	
	drawScore();
	
	SDL_RenderPresent(renderer);
}

void Game::drawScore(){
	// Draw amount of lives
	for(int i=0;i<score.lives;i++){
		SDL_Rect dst = {i*24, 31*12, spriteMap[PacmanEatRight1][sizex], spriteMap[PacmanEatRight1][sizey]};
		SDL_Rect src = {spriteMap[PacmanEatRight1][x], spriteMap[PacmanEatRight1][y], spriteMap[PacmanEatRight1][sizex], spriteMap[PacmanEatRight1][sizey]};
		SDL_RenderCopy(renderer, sheet, &src, &dst);
	}
	
	// Draw fruitbonus
	if(score.fruitbonus){
		SDL_Rect dst = {4*24, 31*12, spriteMap[fruitCherry][sizex], spriteMap[fruitCherry][sizey]};
		SDL_Rect src = {spriteMap[fruitCherry][x], spriteMap[fruitCherry][y], spriteMap[fruitCherry][sizex], spriteMap[fruitCherry][sizey]};
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

