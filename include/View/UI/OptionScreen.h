#ifndef OPTION_SCREEN_H
#define OPTION_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/TextLabel.h"

class OptionScreen : public Screen
{
public:

	OptionScreen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title)
	: Screen(viewMediator, renderer, title)
	{
		initialize();
	}
	
	~OptionScreen()
	{}
	
	bool update(KeyStateArray &keyStateArray) override
	{
		return false;
	}
	
	void render() const override
	{
		for(const auto& widget : mWidgets)
		{
			widget->render();
		}
	}

	void onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification) override
	{}

private:

	void initialize() override
	{
		TextLabel* testLabel = new TextLabel(mRenderer, "Option menu, IMPLEMENT", 0, 0, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(testLabel));
	}

};

#endif