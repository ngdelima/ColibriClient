#ifndef DRONE_SCREEN_H
#define DRONE_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/TextLabel.h"
#include"View/Commands/ViewCommands.h"
#include<iostream>
#include<chrono>

class DroneScreen : public Screen
{
public:

	DroneScreen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title)
	: Screen(viewMediator, renderer, title)
	{
		initialize();
	}
	
	~DroneScreen()
	{
		StopDroneViewCommand* stopDroneViewCommand =
				new StopDroneViewCommand(VIEW_COMMAND_ID::COMMAND_STOP_DRONE);
		mViewMediator->sendViewCommand(stopDroneViewCommand);
	}
	
	bool update(KeyStateArray &keyStateArray) override
	{
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_DOWN)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_DOWN) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_WEST_MOTOR,
														-5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
		}
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_UP)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_UP) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_WEST_MOTOR,
														5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
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

		resetKeyPressedTime(KEY_ID::KEY_W);
		resetKeyPressedTime(KEY_ID::KEY_A);
		resetKeyPressedTime(KEY_ID::KEY_S);
		resetKeyPressedTime(KEY_ID::KEY_D);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_LEFT);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_RIGHT);
	}

	void resetKeyPressedTime(KEY_ID keyId)
	{
		mKeyPressedTime[keyId] = std::chrono::steady_clock::now();
	}

	template<class T>
	T getKeyPressedTime(KEY_ID keyId)
	{
		return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - mKeyPressedTime[keyId]);
	}

	std::map<KEY_ID, std::chrono::time_point<std::chrono::steady_clock>> mKeyPressedTime;

};

#endif