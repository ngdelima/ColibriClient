#ifndef VIEW_H
#define VIEW_H

#include"SDL2/SDL.h"
#include"SDL2/SDL_ttf.h"

#include"View/ScreenManager.h"
#include"View/Input/InputManager.h"
#include<iostream>

class View
{
public:
	
	View();
	~View();
	void run();

private:

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	ScreenManager* mScreenManager;
	InputManager* mInputManager;
	
	void initialize();
	void deintialize();
	void viewLoop();
};


#endif