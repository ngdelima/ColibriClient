#include"SDL/SDL.h"
#include"screen.h"
#include"InputManager.h"
#include"Drone.h"

#include<iostream>

int main(int argc, char* args[])
{
	SDL_Window* window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	window = SDL_CreateWindow(
		"Colibri",		                   // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) 
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() == -1)
	{
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	CommandDispatcher commandDispatcher;
	Drone drone(&commandDispatcher);
	Screen mainScreen(&drone);
	InputManager mInputManager;
	mInputManager.addListener(&drone);
	mInputManager.run();

	float lastFrame = (float)SDL_GetTicks() * 0.001f;
	float currentFrame;
	float elapsedTime;

	SDL_Event event;
	while (SDL_PollEvent(&event) >= 0)
	{
		currentFrame = (float)SDL_GetTicks() * 0.001f;
		elapsedTime = currentFrame - lastFrame;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (!mainScreen.update())
			break;

		mainScreen.render(renderer);

		lastFrame = currentFrame;

		SDL_RenderPresent(renderer);
		SDL_Delay(9);
	}

	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}