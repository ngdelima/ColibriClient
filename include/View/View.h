#ifndef VIEW_H
#define VIEW_H

#include"SDL2/SDL.h"
#include"SDL2/SDL_ttf.h"

#include"View/ViewMediator.h"
#include"View/ScreenManager.h"
#include"View/Input/InputManager.h"
#include"View/Commands/ViewCommands.h"
#include<iostream>

class View : public ViewMediatorComponent
{
public:
	
	View();
	~View();
	void run();
	void onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification) override;
	void onViewCommandSent(ViewCommand* viewCommand) override;

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