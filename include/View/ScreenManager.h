#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include<map>
#include<string>
#include<iostream>

#include"SDL2/SDL.h"

#include"View/ScreenId.h"
#include"View/Screen.h"
#include"View/Input/InputManager.h"
#include"View/UI/MenuScreen.h"
#include"View/UI/DroneScreen.h"
#include"View/UI/OptionScreen.h"

class ScreenManager
{
public:

	ScreenManager(SDL_Window* window, SDL_Renderer* renderer, InputManager* inputManager);
	~ScreenManager();
	bool update();
	void render();
	void changeScreen(SCREEN_ID screenId, std::string title);

private:

	Screen* mCurrentScreen;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	InputManager* mInputManager;

	void initialize();
};

class ScreenFactory
{
public:

	Screen* createScreen(SCREEN_ID screenId, SDL_Renderer* renderer, std::string title)
	{
		switch(screenId)
		{
			case SCREEN_ID::MENU_SCREEN:
			{
				return new MenuScreen(renderer, title);
				break;
			}
			case SCREEN_ID::OPTIONS_SCREEN:
			{
				return new OptionScreen(renderer, title);
				break;
			}
			case SCREEN_ID::DRONE_SCREEN:
			{
				return new DroneScreen(renderer, title);
				break;
			}
			default:
			{
				return nullptr;
				break;
			}
		}
	}
};

#endif