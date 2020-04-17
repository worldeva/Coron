#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(SDL_Window** window, SDL_Renderer** render);
SDL_Surface* loadSurface_Obsolete(std::string filePath);
SDL_Surface* loadSurface(std::string filePath, SDL_Surface** rendScreen);
SDL_Texture* loadTexture(SDL_Renderer** render, std::string filePath);

void close(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture);
void close(SDL_Window** window, SDL_Surface** surf, SDL_Renderer** render, SDL_Texture** texture);