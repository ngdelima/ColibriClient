#ifndef SCREEN_H
#define SCREEN_H

#include"SDL2/SDL.h"
#include"SDL2/SDL_rect.h"
//#include"SDL/SDL_image.h"
#include"SDL2/SDL_ttf.h"

//#include"Drone.h"

#include"View/ViewMediator.h"
#include"View/Input/InputMap.h"
#include"View/Widgets/Widgets.h"
#include"View/ScreenId.h"

#include<string>
#include<vector>

class Screen : public ViewMediatorComponent
{
public:

	Screen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title);
	virtual ~Screen();
	virtual bool update(KeyStateArray &keyStateArray) = 0;
	virtual void render() const = 0;
	SCREEN_ID getNextScreen() const { return mNextScreen; }

protected:

	virtual void initialize();

	SDL_Renderer* mRenderer;
	std::vector<Widget*> mWidgets;
	std::vector<ClickableWidget*> mClickableWidgets;
	std::string mTitle;
	SCREEN_ID mNextScreen;
};


// TODO: Move this drone screen
/*class Screen
{
public:

	Screen(Drone* _drone)
	: mDrone(_drone)
	{
		if (mDrone == nullptr)
			return;

		mMotor1Indicator = new MotorIndicator(mDrone->getMotor1(), "1", 0, 0, 0, "./resources/FreeMono.ttf", 24);
		mMotor2Indicator = new MotorIndicator(mDrone->getMotor2(), "2", 0, 0, 100, "./../resources/FreeMono.ttf", 24);
		mMotor3Indicator = new MotorIndicator(mDrone->getMotor3(), "3", 0, 0, 200, "./../resources/FreeMono.ttf", 24);
		mMotor4Indicator = new MotorIndicator(mDrone->getMotor4(), "4", 0, 0, 300, "./../resources/FreeMono.ttf", 24);
	}

	bool update()
	{
		mMotor1Indicator->update();
		mMotor2Indicator->update();
		mMotor3Indicator->update();
		mMotor4Indicator->update();

		return true;
	}

	void render(SDL_Renderer* renderer)
	{
		mMotor1Indicator->render(renderer);
		mMotor2Indicator->render(renderer);
		mMotor3Indicator->render(renderer);
		mMotor4Indicator->render(renderer);
	}

private:

	Drone* mDrone;

	MotorIndicator* mMotor1Indicator;
	MotorIndicator* mMotor2Indicator;
	MotorIndicator* mMotor3Indicator;
	MotorIndicator* mMotor4Indicator;

};*/

#endif