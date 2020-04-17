#include "../../include/screen/Source.h"

bool init(SDL_Window** window, SDL_Renderer** render)
{
	bool ret = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		*window = SDL_CreateWindow("DMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			
			*render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
			
			if (*render == NULL)
			{
				
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				ret = false;
			}
			else
			{
			
				SDL_SetRenderDrawColor(*render, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(*render);
				printf(SDL_GetError());
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					ret = false;
				}
			}
		}
	}
		
	return ret;
}

SDL_Surface* loadSurface(std::string filePath, SDL_Surface** rendScreen)
{
	//Loads 32 bit BMP
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(filePath.c_str());
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
	else
	{
		surface = SDL_ConvertSurface(surface, (*rendScreen)->format, 0);
		if (surface == NULL)
		{
			printf("Unable to convert image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
		}
	}
	return surface;
}

SDL_Texture* loadTexture(SDL_Renderer** render, std::string filePath)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(*render, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

SDL_Surface* loadSurface_Obsolete(std::string filePath)
{
	//Obsolete; Loads 24 bit BMP
	SDL_Surface* ret = NULL;
	ret = SDL_LoadBMP(filePath.c_str());
	if (ret == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
	}
	return ret;
}

void close(SDL_Window** window, SDL_Surface** surf, SDL_Renderer** render, SDL_Texture** texture)
{
	SDL_FreeSurface(*surf);
	*surf = NULL;
	SDL_DestroyTexture(*texture);
	*texture = NULL;
	SDL_DestroyRenderer(*render);
	*render = NULL;
	SDL_DestroyWindow(*window);
	*window = NULL;
	IMG_Quit();
	SDL_Quit();
}

void close(SDL_Window** window, SDL_Renderer** render, SDL_Texture** texture)
{
	SDL_DestroyTexture(*texture);
	*texture = NULL;
	SDL_DestroyRenderer(*render);
	*render = NULL;
	SDL_DestroyWindow(*window);
	*window = NULL;
	IMG_Quit();
	SDL_Quit();
}
