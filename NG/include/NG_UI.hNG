/*
 * UI.h
 *
 *  Created on: Jan 29, 2015
 *      Author: frits
 *       Group: TA's
 */

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "GameObjectStruct.h"

class UI {
public:
	/**
	 * Constructor
	 * @param map the map of the board
	 */
	UI(std::vector<std::vector<int>> map);
	virtual ~UI();

	void init();

	/**
	 * Setter for the score.
	 * @param score score
	 */
	void setScore(int score);

	/**
	 * Setter for the lives.
	 * @param score lives
	 */
	void setLives(int lives);


	/**
	 * Update the screen
	 * - Draw the background
	 * - Draw the score
	 * - Draw the remaining lives
	 * - Draw the objecst in the argument
	 * @param objects list of object that must be drawn
	 */
	void update(std::vector<GameObjectStruct> objects);

private:
	/**
	 * Loads the sprite sheet.
	 */
	void loadTextures();

	/**
	 * Load the maps that contains all the clipping masks.
	 *
	 * Works as follows:
	 * clips[<type>][<direction>]
	 */
	void loadMaps();

	/**
	 * Places the walls in the correct places.
	 */
	void drawBackground(std::vector<std::vector<int>> & map);

	/**
    * Draws the score.
    */
	void drawScore();

	/**
    * Draws the lives.
    */
	void drawLives();

	/**
	* Loads an image into a texture on the rendering device
	* @param file The image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

private:
	/* Score and lives */
	int score = 0;
	int lives = 3;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *sheet;

	/* 2d array containing the map, a 1 is a wall. */
	std::vector<std::vector<int>> map;

	/* Map containing all the game objects */
	std::map<Type,std::map<Direction, SDL_Rect>> clips;
};

#endif /* SRC_UI_H_ */
