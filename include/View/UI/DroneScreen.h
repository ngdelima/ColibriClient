#ifndef DRONE_SCREEN_H
#define DRONE_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/TextLabel.h"
#include<iostream>

class DroneScreen : public Screen
{
public:

	DroneScreen(SDL_Renderer* renderer, std::string title)
	: Screen(renderer, title)
	{
		initialize();
	}
	
	~DroneScreen()
	{}
	
	void update(KeyStateArray &keyStateArray) override
	{
	}
	
	void render() const override
	{
		for(const auto& widget : mWidgets)
		{
			widget->render();
		}
	}

private:

	void initialize() override
	{
		TextLabel* testLabel = new TextLabel(mRenderer, "Drone screen, IMPLEMENT", 0, 0, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(testLabel));
	}

};

#endif