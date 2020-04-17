#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include "include/screen/cScreen.h"
#include "include/screen/tSprite.h"
#include <vector>

class platform
{
public:
	void playerInput(const Uint8* keystate);
	int playerPosition = 224;
};

void platform::playerInput(const Uint8* keystate)
{
	if (keystate[SDL_SCANCODE_A] && (playerPosition >= 16))
	{
		playerPosition = playerPosition - 5;
	}
	if (keystate[SDL_SCANCODE_D] && (playerPosition <= 446))
	{
		playerPosition = playerPosition + 5;
	}
}

class ball
{
public:
	int xVel;
	int yVel;
	int xPos;
	int yPos;
	int radius = 16;
};

class cube
{
public:
	cube(int number, int yNumber);
	void moveDown();
	int xPosition;
	int yPosition;
	int health = 1;
};

cube::cube(int xNumber, int yNumber)
{
	xPosition = 64 * xNumber;
	yPosition = 32 * yNumber;
}

void cube::moveDown()
{
	yPosition = yPosition + 2;
}

int main(int argc, char* args[])
{
	const int SCREEN_WIDTH = 448;
	const int SCREEN_HEIGHT = 768;
	std::vector<cube*> allCubes;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			allCubes.push_back(new cube(j, i));
		}
	}
	std::srand(NULL);
	SDL_Event e;
	int ballNumber = 1;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	bool playerControl = true;
	bool quit = false;
	platform player;
	init();
	cScreen user(SCREEN_WIDTH, SCREEN_HEIGHT, 0xFF, 0xFF, 0xFF, 0xFF);
	spriteSheet circle("assets/dots.png", user.getRenderer(), 100, 100);
	while (!quit)
	{
		SDL_PumpEvents();
		user.clearRender();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
		player.playerInput(keystate);
		circle.renderSprite(0, 0, player.playerPosition % 3);
		user.updateRender();
	}
	user.updateRender();
	return 0;
}



/*	std::srand(NULL);
	SDL_Event e;
	int ballNumber = 1;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	bool playerControl = true;
	bool quit = false;
	int playerPos = 224;
	init();
	cScreen user(448, 768);
	tSprite circle("assets/circle.bmp", user.getRenderer());
	tSprite square("assets/square.bmp", user.getRenderer());
	while (!quit)
	{
		SDL_PumpEvents();
		user.clearRender();
		while (SDL_PollEvent(&e)!=0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
		if (keystate[SDL_SCANCODE_A] && (playerPos >= 16))
		{
			playerPos = playerPos - 5;
		}
		if (keystate[SDL_SCANCODE_D] && (playerPos <= 430))
		{
			playerPos = playerPos + 5;
		}
		if (keystate[SDL_SCANCODE_SPACE])
		{
			printf("pressed space");
			playerControl = false;
		}
		if (playerControl = false)
		{

		}
		circle.renderSprite(playerPos - 16, 768 - 32);
		user.updateRender();
	}
	user.updateRender();
	return 0;
	*/
/*
	SDL_Window* window = NULL;
	SDL_Renderer* scrnRender = NULL;
	SDL_Texture* scrnTexture = NULL;
	if (!init(&window, &scrnRender))
	{
		printf("SDL Initialization Failed \n");
	}

	scrnTexture = loadTexture(&scrnRender, "assets/Hello_World.bmp");
	SDL_Event e;

	bool exit = false;

	while (!exit)
	{
		SDL_RenderClear(scrnRender);
		SDL_RenderCopy(scrnRender, scrnTexture, NULL, NULL);
		SDL_RenderPresent(scrnRender);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				exit = true;
			}
		}
	}
	close(&window, &scrnRender, &scrnTexture);
	return 0;
	*/

/*
	printf("1");
	init();
	cScreen user(640, 480, 0x5F, 0x6F, 0x75, 0xFF);
	user.clearRender();
	user.loadTexture("assets/Hello_World.bmp");
	user.copyRender(NULL, NULL);
	user.updateRender();
	printf(SDL_GetError());
	SDL_Delay(2000);
	return 0;
	*/