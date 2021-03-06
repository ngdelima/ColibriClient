#ifndef DRONE_SCREEN_H
#define DRONE_SCREEN_H

#include"View/Screen.h"
#include"View/Widgets/TextLabel.h"
#include"View/Commands/ViewCommands.h"
#include"Logging/Logging.h"
#include"ViewModel/ViewModel.h"
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
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_W)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_W) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_WEST_MOTOR,
														5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_W);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_W);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_S)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_S) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_WEST_MOTOR,
														-5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_S);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_S);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_D)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_D) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::SOUTH_WEST_MOTOR,
														5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_D);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_D);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_A)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_A) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::SOUTH_WEST_MOTOR,
														-5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_A);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_A);
		}
		
		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_UP)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_UP) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_EAST_MOTOR,
														5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_DOWN)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_DOWN) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::NORTH_EAST_MOTOR,
														-5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_RIGHT)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_RIGHT) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::SOUTH_EAST_MOTOR,
														5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_RIGHT);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_RIGHT);
		}

		if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_LEFT)] == INPUT_STATE::PRESSED)
		{
			if(getKeyPressedTime<std::chrono::milliseconds>(KEY_ID::KEY_ARROW_LEFT) > std::chrono::milliseconds(200))
			{
				SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
						new SetMotorSpeedViewCommand(	VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED,
														MOTOR_ID::SOUTH_EAST_MOTOR,
														-5);
				mViewMediator->sendViewCommand(setMotorSpeedViewCommand);

				resetKeyPressedTime(KEY_ID::KEY_ARROW_LEFT);
			}
		}
		else
		{
			resetKeyPressedTime(KEY_ID::KEY_ARROW_LEFT);
		}

		updateWidgets();

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
		TextLabel* northEastMotorSpeedLabel = new TextLabel(mRenderer, "NE: 0", 0, 0, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(northEastMotorSpeedLabel));

		TextLabel* northWestMotorSpeedLabel = new TextLabel(mRenderer, "NW: 0", 0, 100, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(northWestMotorSpeedLabel));

		TextLabel* southEastMotorSpeedLabel = new TextLabel(mRenderer, "SE: 0", 0, 200, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(southEastMotorSpeedLabel));

		TextLabel* southWestMotorSpeedLabel = new TextLabel(mRenderer, "SW: 0", 0, 300, "./resources/FreeMono.ttf", 24);
		mWidgets.push_back(dynamic_cast<Widget*>(southWestMotorSpeedLabel));

		// Send command to start Drone object
		StartDroneViewCommand* startDroneViewCommand =
				new StartDroneViewCommand(VIEW_COMMAND_ID::COMMAND_START_DRONE);
		mViewMediator->sendViewCommand(startDroneViewCommand);

		// Send command to pair DroneViewModel to Drone instance
		SetViewModelDroneViewCommand* setViewModelDroneViewCommand =
				new SetViewModelDroneViewCommand(VIEW_COMMAND_ID::COMMAND_SET_VIEW_MODEL_DRONE);
		setViewModelDroneViewCommand->mViewModel = &mDroneViewModel;
		mViewMediator->sendViewCommand(setViewModelDroneViewCommand);

		resetKeyPressedTime(KEY_ID::KEY_W);
		resetKeyPressedTime(KEY_ID::KEY_A);
		resetKeyPressedTime(KEY_ID::KEY_S);
		resetKeyPressedTime(KEY_ID::KEY_D);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_UP);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_DOWN);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_LEFT);
		resetKeyPressedTime(KEY_ID::KEY_ARROW_RIGHT);

		Logging::log("DroneScreen", "Initialize done");
	}

	void updateWidgets()
	{
		mDroneViewModel.update();
		dynamic_cast<TextLabel*>(mWidgets[0])->setText("NE: " + std::to_string(mDroneViewModel.mNorthEastMotorSpeed));
		dynamic_cast<TextLabel*>(mWidgets[1])->setText("NW: " + std::to_string(mDroneViewModel.mNorthWestMotorSpeed));
		dynamic_cast<TextLabel*>(mWidgets[2])->setText("SE: " + std::to_string(mDroneViewModel.mSouthEastMotorSpeed));
		dynamic_cast<TextLabel*>(mWidgets[3])->setText("SW: " + std::to_string(mDroneViewModel.mSouthWestMotorSpeed));
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
	DroneViewModel mDroneViewModel;

};

#endif