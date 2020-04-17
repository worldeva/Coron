#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "cScreen.h"

class spriteSheet
{
public:
	spriteSheet();
	spriteSheet(std::string filePath, SDL_Renderer* renderer);
	spriteSheet(std::string filePath, SDL_Renderer* renderer, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	spriteSheet(std::string filePath, SDL_Renderer* renderer, int xDimension, int yDimension, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);


	~spriteSheet();

	void freeTexture();
	void setTexture(std::string filePath);
	void setTexture(std::string filePath, int xDimension, int yDimension, Uint8 r, Uint8 g, Uint8 b);
	void setTexture(std::string filePath, Uint8 r, Uint8 g, Uint8 b);
	void setRenderer(SDL_Renderer* renderer);

	void renderSprite(int x, int y);
	void renderSprite(int x, int y, int clipNum);


private:
	SDL_Texture* tSheet;
	SDL_Renderer* render;

	std::vector <SDL_Rect*> spriteClip;
	
	int spriteHeight;
	int spriteWidth;
};