#include "../../include/screen/cScreen.h"

cScreen::cScreen()
{
	screenWidth = 0;
	screenHeight = 0;
	window = NULL;
	surface = NULL;
	nSurface = NULL;
	render = NULL;
	texture = NULL;
}

cScreen::cScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	window = NULL;
	surface = NULL;
	nSurface = NULL;
	render = NULL;
	texture = NULL;
	window = SDL_CreateWindow("DMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		surface = SDL_GetWindowSurface(window);
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		if (render == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
		}
	}
}

cScreen::cScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;
	window = NULL;
	surface = NULL;
	nSurface = NULL;
	render = NULL;
	texture = NULL;
	window = SDL_CreateWindow("DMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		surface = SDL_GetWindowSurface(window);
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
		if (render == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetRenderDrawColor(render, R, G, B, A);
		}
	}
}

cScreen::~cScreen()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyRenderer(render);
	render = NULL;
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_FreeSurface(nSurface);
	nSurface = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
}

SDL_Renderer* cScreen::getRenderer()
{
	return render;
}

void cScreen::loadSurface(std::string filePath)
{
	SDL_FreeSurface(nSurface);

	nSurface = NULL;

	nSurface = IMG_Load(filePath.c_str());
	if (nSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
	else
	{
		nSurface = SDL_ConvertSurface(nSurface, surface->format, 0);
		if (nSurface == NULL)
		{
			printf("Unable to convert image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
		}
	}
}

void cScreen::loadSurface_Obsolete(std::string filePath)
{
	SDL_FreeSurface(nSurface);

	nSurface = NULL;

	nSurface = IMG_Load(filePath.c_str());
	if (nSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
}

void cScreen::loadTexture(std::string filePath)
{
	SDL_DestroyTexture(texture);

	texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(render, loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
}

void cScreen::copyRender(SDL_Rect* source, SDL_Rect* dest)
{
	SDL_RenderCopy(render, texture, source, dest);
}

void cScreen::updateRender()
{
	SDL_RenderPresent(render);
}

void cScreen::clearRender()
{
	SDL_RenderClear(render);
}

void cScreen::copySurface(SDL_Rect* source, SDL_Rect* dest)
{
	SDL_BlitSurface(surface, source, nSurface, dest);
}

void cScreen::updateSurface()
{
	SDL_UpdateWindowSurface(window);
}

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
}

void quit()
{
	IMG_Quit();
	SDL_Quit();
}