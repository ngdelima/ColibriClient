#ifndef VIEW_COMMANDS_H
#define VIEW_COMMANDS_H

enum class VIEW_COMMAND_ID
{
	COMMAND_FIRST = 0,
	COMMAND_START_DRONE = COMMAND_FIRST,
	COMMAND_SET_MOTOR_SPEED,
	COMMAND_STOP_DRONE,
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

class StopDroneViewCommand : public ViewCommand
{
public:
	StopDroneViewCommand(VIEW_COMMAND_ID id)
	: ViewCommand(id)
	{}
	// TODO: No params at the moment, later add usb port and other stuff
};

#endif