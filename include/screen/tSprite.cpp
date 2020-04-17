#include "../../include/screen/tSprite.h"

spriteSheet::spriteSheet()
{
    tSheet = NULL;
    spriteHeight = 0;
    spriteWidth = 0;
    render = NULL;
}

spriteSheet::spriteSheet(std::string filePath, SDL_Renderer* renderer)
{
    spriteHeight = 0;
    spriteWidth = 0;
    setRenderer(renderer);
    setTexture(filePath);
}

spriteSheet::spriteSheet(std::string filePath, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
    spriteHeight = 0;
    spriteWidth = 0;
    setRenderer(renderer);
    setTexture(filePath, r, g, b);
}

spriteSheet::spriteSheet(std::string filePath, SDL_Renderer* renderer, int xDimension, int yDimension, Uint8 r, Uint8 g, Uint8 b)
{
    spriteHeight = 0;
    spriteWidth = 0;
    setRenderer(renderer);
    setTexture(filePath, xDimension, yDimension, r, g, b);
}

spriteSheet::~spriteSheet()
{
    freeTexture();
    render = NULL;
}

void spriteSheet::freeTexture()
{
	SDL_DestroyTexture(tSheet);
	tSheet = NULL;
}

void spriteSheet::setTexture(std::string filePath)
{
    freeTexture();
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (tempSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
    }
    else
    {
        spriteHeight = tempSurface->h;
        spriteWidth = tempSurface->w;
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));
        tSheet = SDL_CreateTextureFromSurface(render, tempSurface);
    }
    spriteClip.push_back(new SDL_Rect({ 0, 0, spriteWidth, spriteHeight }));
}

void spriteSheet::renderSprite(int x, int y)
{
    printf("\n%i",spriteWidth);
    printf("\n%i", spriteHeight);
    SDL_Rect renderQuad = { x, y, spriteWidth, spriteHeight };
    SDL_RenderCopy(render, tSheet, NULL, &renderQuad);
}

void spriteSheet::renderSprite(int x, int y, int clipNum)
{
    printf("%i", spriteClip[clipNum]->x);
    printf(",%i", spriteClip[clipNum]->y);
    printf(",%i", spriteClip[clipNum]->w);
    printf(",%i", spriteClip[clipNum]->h);
    SDL_Rect renderQuad = { x, y, spriteWidth, spriteHeight };
    SDL_RenderCopy(render, tSheet, spriteClip[clipNum], &renderQuad);

}

void spriteSheet::setTexture(std::string filePath, int xDimension, int yDimension, Uint8 r, Uint8 g, Uint8 b)
{
	freeTexture();
	SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (tempSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
    }
    else
    {
        spriteWidth = xDimension;
        spriteHeight = yDimension;
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, r, g, b));
        tSheet = SDL_CreateTextureFromSurface(render, tempSurface);
    }
    for (int i = 0; i < tempSurface->h/spriteHeight; i++)
    {
        for (int j = 0; j < tempSurface->w/spriteWidth; j++)
        {
            printf("\n%i", i);
            printf("\n%i", j);
            spriteClip.push_back(new SDL_Rect({ j * xDimension, i * yDimension, xDimension, yDimension }));
        }
    }
}

void spriteSheet::setTexture(std::string filePath, Uint8 r, Uint8 g, Uint8 b)
{
    freeTexture();
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (tempSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
    }
    else
    {
        spriteHeight = tempSurface->h;
        spriteWidth = tempSurface->w;
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, r, g, b));
        tSheet = SDL_CreateTextureFromSurface(render, tempSurface);
    }
    SDL_FreeSurface(tempSurface);
}

void spriteSheet::setRenderer(SDL_Renderer* renderer)
{
    render = renderer;
}
