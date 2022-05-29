#ifndef VIEW_COMMANDS_H
#define VIEW_COMMANDS_H

#include<queue>
#include<mutex>

//#include"ViewModel/ViewModel.h"

// TODO: Drone commands should be in Model, View commands here
enum class VIEW_COMMAND_ID
{
	COMMAND_FIRST = 0,
	FIRST_DRONE_COMMAND = COMMAND_FIRST, 
	COMMAND_START_DRONE = FIRST_DRONE_COMMAND,
	COMMAND_SET_VIEW_MODEL_DRONE,
	COMMAND_SET_MOTOR_SPEED,
	COMMAND_SET_MOTOR_SPEED_DELTA,
	COMMAND_STOP_DRONE,
	LAST_DRONE_COMMAND = COMMAND_STOP_DRONE,
	COMMAND_LAST = COMMAND_STOP_DRONE,
};

// TODO: change next enum with model enum
enum class MOTOR_ID
{
	MOTOR_FIRST = 0,
	NORTH_EAST_MOTOR = MOTOR_FIRST,
	NORTH_WEST_MOTOR,
	SOUTH_EAST_MOTOR,
	SOUTH_WEST_MOTOR,
	MOTOR_LAST = SOUTH_WEST_MOTOR,
};

class ViewCommand
{
public:
	ViewCommand(VIEW_COMMAND_ID id)
	: mId(id)
	{}

	virtual ~ViewCommand(){}

	VIEW_COMMAND_ID mId;
};

class StartDroneViewCommand : public ViewCommand
{
public:
	StartDroneViewCommand(VIEW_COMMAND_ID id)
	: ViewCommand(id)
	{}
	// TODO: No params at the moment, later add usb port and other stuff
};

class SetMotorSpeedViewCommand : public ViewCommand
{
public:
	SetMotorSpeedViewCommand(VIEW_COMMAND_ID id, MOTOR_ID motorId, int speed)
	: ViewCommand(id)
	, mMotorId(motorId)
	, mMotorSpeed(speed)
	{}

	MOTOR_ID mMotorId;
	int mMotorSpeed;
};

class SetMotorSpeedDeltaViewCommand : public ViewCommand
{
public:
	SetMotorSpeedDeltaViewCommand(VIEW_COMMAND_ID id, MOTOR_ID motorId, int speed)
	: ViewCommand(id)
	, mMotorId(motorId)
	, mMotorSpeed(speed)
	{}

	MOTOR_ID mMotorId;
	int mMotorSpeed;
};


class StopDroneViewCommand : public ViewCommand
{
public:
	StopDroneViewCommand(VIEW_COMMAND_ID id)
	: ViewCommand(id)
	{}
	// TODO: No params at the moment, later add usb port and other stuff
};
class DroneViewModel;
class SetViewModelDroneViewCommand : public ViewCommand
{
public:
	SetViewModelDroneViewCommand(VIEW_COMMAND_ID id)
	: ViewCommand(id)
	{}
	
	DroneViewModel* mViewModel;
};

class ThreadSafeViewCommandQueue
{
public:

	void addCommand(ViewCommand* viewCommand)
	{
		mQueueMutex.lock();

		mQueue.push(viewCommand);

		mQueueMutex.unlock();
	}

	ViewCommand* getCommand()
	{
		ViewCommand* viewCommand = nullptr;

		mQueueMutex.lock();

		if(mQueue.size() > 0)
		{
			viewCommand = mQueue.front();
			mQueue.pop();	
		}

		mQueueMutex.unlock();

		return viewCommand;
	}

private:

	std::queue<ViewCommand*> mQueue;
	std::mutex mQueueMutex;

};

#endif