#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include<map>
#include<string>
#include<iostream>

#include"SDL2/SDL.h"

#include"View/ViewMediator.h"
#include"View/ScreenId.h"
#include"View/Screen.h"
#include"View/Input/InputManager.h"
#include"View/UI/MenuScreen.h"
#include"View/UI/DroneScreen.h"
#include"View/UI/OptionScreen.h"

class ScreenManager : public ViewMediatorComponent
{
public:

	ScreenManager(ViewMediator* viewMediator, SDL_Window* window, SDL_Renderer* renderer, InputManager* inputManager);
	~ScreenManager();
	bool update();
	void render();
	void changeScreen(SCREEN_ID screenId, std::string title);
	void onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification) override;

private:

	Screen* mCurrentScreen;
	SCREEN_ID mNextScreen;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	InputManager* mInputManager;

	void initialize();
};

class ScreenFactory
{
public:

	static Screen* createScreen(SCREEN_ID screenId,
								SDL_Renderer* renderer,
								std::string title,
								ViewMediator* viewMediator)
	{
		switch(screenId)
		{
			case SCREEN_ID::MENU_SCREEN:
			{
				return new MenuScreen(viewMediator, renderer, title);
				break;
			}
			case SCREEN_ID::OPTIONS_SCREEN:
			{
				return new OptionScreen(viewMediator, renderer, title);
				break;
			}
			case SCREEN_ID::DRONE_SCREEN:
			{
				return new DroneScreen(viewMediator, renderer, title);
				break;
			}
			case SCREEN_ID::NO_SCREEN:
			default:
			{
				return nullptr;
				break;
			}
		}
	}
};

#endif