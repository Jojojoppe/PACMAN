#include <iostream>
#include <Game.h>

#include <SDL2/SDL.h>

int main(int argc, char * argv[]){
	
	Game G;
	G.main();
	
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
		}
	}
	
	SDL_RemoveTimer(G.timer);
	
	return 0;
}
