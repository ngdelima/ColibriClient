#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/MenuTile.h"
#include"View/Commands/ViewCommands.h"
#include<iostream>
#include<functional>

class MenuScreen : public Screen
{
public:

	MenuScreen(SDL_Renderer* renderer, std::string title)
	: Screen(renderer, title)
	{
		initialize();
	}
	
	~MenuScreen()
	{}
	
	void update(KeyStateArray &keyStateArray) override
	{
		//keyStateArray[static_cast<size_t>(0)] = INPUT_STATE::NOT_PRESSED;
		//keyStateArray[static_cast<size_t>(KEY_ID::KEY_ESC)] == INPUT_STATE::PRESSED
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ENTER)] == INPUT_STATE::PRESSED)
		{
			mCurrentMenuTile->onClick();
		}
	}
	
	void render() const override
	{
		//std::cout << "Menu screen rendered" << '\n';
		for(const auto& widget : mWidgets)
		{
			widget->render();
		}
	}

private:

	void initialize() override
	{
		MenuTile* startDroneTile = new MenuTile(mRenderer,
												"Start Drone",
												0, 0,
												"./resources/FreeMono.ttf", 24
												, std::bind(&MenuScreen::navigateToDroneScreen, this));
		startDroneTile->setIsHighlighted(true);
		mCurrentMenuTile = startDroneTile;

		mWidgets.push_back(dynamic_cast<Widget*>(startDroneTile));

		MenuTile* testTile = new MenuTile( mRenderer,
											"Test tile",
											0, 100,
											"./resources/FreeMono.ttf", 24
											, std::bind(&MenuScreen::navigateToDroneScreen, this));

		mWidgets.push_back(dynamic_cast<Widget*>(testTile));


	}

	void navigateToDroneScreen()
	{
		

	}

	MenuTile* mCurrentMenuTile;

};

#endif