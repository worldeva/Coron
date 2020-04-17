#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "tSprite.h"

class cScreen
{
public:
	cScreen();
	cScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	cScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	~cScreen();

	SDL_Renderer* getRenderer();

	void loadSurface(std::string filePath);
	void loadSurface_Obsolete(std::string filePath);
	void loadTexture(std::string filePath);

	void copyRender(SDL_Rect* source, SDL_Rect* dest);
	void updateRender();
	void copySurface(SDL_Rect* source, SDL_Rect* dest);
	void updateSurface();
	void clearRender();
private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* nSurface;
	SDL_Renderer* render;
	SDL_Texture* texture;
	int screenWidth;
	int screenHeight;
};

void init();