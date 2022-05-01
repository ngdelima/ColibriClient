#ifndef DRONE_SCREEN_H
#define DRONE_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/TextLabel.h"
#include"View/Commands/ViewCommands.h"
#include<iostream>

class DroneScreen : public Screen
{
public:

	DroneScreen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title)
	: Screen(viewMediator, renderer, title)
	{
		initialize();
	}
	
	~DroneScreen()
	{}
	
	bool update(KeyStateArray &keyStateArray) override
	{
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ENTER)] == INPUT_STATE::PRESSED)
		{
			StopDroneViewCommand* stopDroneViewCommand =
				new StopDroneViewCommand(VIEW_COMMAND_ID::COMMAND_STOP_DRONE);
			mViewMediator->sendViewCommand(stopDroneViewCommand);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_DOWN)] == INPUT_STATE::PRESSED)
		{
			/*if(mDownKeyWasPressed == false)
			{
				// TODO: CREATE COMMAND AND SEND
				mViewMediator->sendViewCommand();
				mDownKeyWasPressed = true;
			}*/
			SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
					new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
													MOTOR_ID::NORTH_EAST_MOTOR,
													0);
			mViewMediator->sendViewCommand(setMotorSpeedViewCommand);
		}
		else
		{
		//	mDownKeyWasPressed = false;
		}
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_UP)] == INPUT_STATE::PRESSED)
		{
			// if(mUpKeyWasPressed == false)
			// {
				
			// 	mUpKeyWasPressed = true;
			// }
		}
		else
		{
			//mUpKeyWasPressed = false;
		}

		//return !mShouldNavigate;
		return true;
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
		TextLabel* testLabel = new TextLabel(mRenderer, "Drone screen, IMPLEMENT", 0, 0, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(testLabel));

		// Send command to start Drone object
		StartDroneViewCommand* startDroneViewCommand =
				new StartDroneViewCommand(VIEW_COMMAND_ID::COMMAND_START_DRONE);
		mViewMediator->sendViewCommand(startDroneViewCommand);
	}

};

#endif