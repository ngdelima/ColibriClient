#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include"View/ScreenId.h"
#include"View/Screen.h"
#include"View/Widgets/MenuTile.h"
#include"View/Commands/ViewCommands.h"
#include<iostream>
#include<functional>

class MenuScreen : public Screen
{
public:

	MenuScreen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title)
	: Screen(viewMediator, renderer, title)
	, mCurrentClickableWidgetIndex(0)
	, mShouldNavigate(false)
	{
		initialize();
	}
	
	~MenuScreen()
	{}
	
	bool update(KeyStateArray &keyStateArray) override
	{
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ENTER)] == INPUT_STATE::PRESSED)
		{
			mCurrentClickableWidget->onClick();
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_DOWN)] == INPUT_STATE::PRESSED)
		{
			if(mDownKeyWasPressed == false)
			{
				goToNextClickableWidget();
				mDownKeyWasPressed = true;
			}
		}
		else
		{
			mDownKeyWasPressed = false;
		}
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_UP)] == INPUT_STATE::PRESSED)
		{
			if(mUpKeyWasPressed == false)
			{
				goToNextClickableWidget();
				mUpKeyWasPressed = true;
			}
		}
		else
		{
			mUpKeyWasPressed = false;
		}

		return !mShouldNavigate;
	}
	
	void render() const override
	{
		//std::cout << "Menu screen rendered" << '\n';
		for(const auto& widget : mWidgets)
		{
			widget->render();
		}
		for(const auto& widget : mClickableWidgets)
		{
			widget->render();
		}
	}

	void onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification) override
	{
		switch(notification)
		{
			default:
			break;
		}
	}

private:

	void initialize() override
	{
		MenuTile* startDroneTile = new MenuTile(mRenderer,
												"Start Drone",
												0, 0,
												10, 10,
												"./resources/FreeMono.ttf", 24
												, std::bind(&MenuScreen::navigateToDroneScreen, this));
		startDroneTile->setIsHighlighted(true);
		mCurrentClickableWidget = startDroneTile;

		mClickableWidgets.push_back(dynamic_cast<ClickableWidget*>(startDroneTile));

		MenuTile* testTile = new MenuTile( mRenderer,
											"Test tile",
											0, 100,
											10, 10,
											"./resources/FreeMono.ttf", 24
											, std::bind(&MenuScreen::navigateToOptionsScreen, this));

		mClickableWidgets.push_back(dynamic_cast<ClickableWidget*>(testTile));
	}

	void navigateToDroneScreen()
	{
		mNextScreen = SCREEN_ID::DRONE_SCREEN;
		mShouldNavigate = true;
		mViewMediator->notify(this, VIEW_NOTIFICATION::SCREEN_NAVIGATE);
	}

	void navigateToOptionsScreen()
	{
		mNextScreen = SCREEN_ID::OPTIONS_SCREEN;
		mShouldNavigate = true;
		mViewMediator->notify(this, VIEW_NOTIFICATION::SCREEN_NAVIGATE);
	}

	void goToNextClickableWidget()
	{
		mCurrentClickableWidget->setIsHighlighted(false);

		mCurrentClickableWidgetIndex++;

		if(mCurrentClickableWidgetIndex >= mClickableWidgets.size())
		{
			mCurrentClickableWidgetIndex = 0;
		}

		mCurrentClickableWidget = mClickableWidgets[mCurrentClickableWidgetIndex];
		mCurrentClickableWidget->setIsHighlighted(true);
	}
	
	void goToPreviousClickableWidget()
	{
		mCurrentClickableWidget->setIsHighlighted(false);

		mCurrentClickableWidgetIndex--;

		if(mCurrentClickableWidgetIndex < 0)
		{
			mCurrentClickableWidgetIndex = mClickableWidgets.size() - 1;
		}

		mCurrentClickableWidget = mClickableWidgets[mCurrentClickableWidgetIndex];
		mCurrentClickableWidget->setIsHighlighted(true);
	}

	ClickableWidget* mCurrentClickableWidget;
	int mCurrentClickableWidgetIndex;
	bool mShouldNavigate;
	bool mDownKeyWasPressed;
	bool mUpKeyWasPressed;
};

#endif