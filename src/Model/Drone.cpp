#include"Model/Drone.h"
#include"Logging/Logging.h"

Drone::Drone(Communication* communication)
: mCommunication(communication)
{
	mMotorSpeeds.insert(std::pair<MOTOR_ID, int>(MOTOR_ID::NORTH_EAST_MOTOR, 0));
	mMotorSpeeds.insert(std::pair<MOTOR_ID, int>(MOTOR_ID::NORTH_WEST_MOTOR, 0));
	mMotorSpeeds.insert(std::pair<MOTOR_ID, int>(MOTOR_ID::SOUTH_EAST_MOTOR, 0));
	mMotorSpeeds.insert(std::pair<MOTOR_ID, int>(MOTOR_ID::SOUTH_WEST_MOTOR, 0));
}

void Drone::run()
{
	Logging::log("Drone", "Start drone from run");

	StartDroneViewCommand* startDroneViewCommand =
		new StartDroneViewCommand(VIEW_COMMAND_ID::COMMAND_START_DRONE);

	uint8_t* cmd = nullptr;
	int size = CommandSerializer::serializeCommand(startDroneViewCommand, &cmd);
	mCommunication->send(cmd, size);

	// Wait for drone response, possible memory leak
	std::string reading;
	while( !mCommunication->getReading(&reading) &&
			reading != "Start drone")
	{
		Logging::log("Drone", "Waiting for drone start confirmation");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		mCommunication->send(cmd, size);
	}
	Logging::log("Drone", "Received drone started message, running drone");
}

void Drone::addCommand(ViewCommand* viewCommand)
{
	//TODO: Add params: Logging::log("Drone", "addCommand", (int)viewCommand->mId);
	Logging::log("Drone", "addCommand");
	switch(viewCommand->mId)
	{
		case VIEW_COMMAND_ID::COMMAND_START_DRONE:
		{
			Logging::log("Drone", "Start drone");
			uint8_t* cmd = nullptr;
			int size = CommandSerializer::serializeCommand(viewCommand, &cmd);
			mCommunication->send(cmd, size);
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED:
		{
			Logging::log("Drone", "Set motor speed");
			SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
					dynamic_cast<SetMotorSpeedViewCommand*>(viewCommand);

			int speed = setMotorSpeedViewCommand->mMotorSpeed;
			if(speed < 0) speed = 0;
			else if(100 < speed) speed = 100;
			setMotorSpeedViewCommand->mMotorSpeed = speed;

			MOTOR_ID motorId = setMotorSpeedViewCommand->mMotorId;
			mMotorSpeeds[motorId] = speed;

			uint8_t* cmd;
			int size = CommandSerializer::serializeCommand(viewCommand, &cmd);
			mCommunication->send(cmd, size);
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED_DELTA:
		{
			Logging::log("Drone:", "Set motor speed delta");
			SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
					dynamic_cast<SetMotorSpeedViewCommand*>(viewCommand);

/*			MOTOR_ID motorId = setMotorSpeedViewCommand->mMotorId;
			int speed =  setMotorSpeedViewCommand->mMotorSpeed;
			if(speed < 0) speed = 0;
			else if(100 < speed) speed = 100;
			mMotorSpeeds[motorId] = speed;
*/

			uint8_t* cmd;
			int size = CommandSerializer::serializeCommand(viewCommand, &cmd);
			mCommunication->send(cmd, size);
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_STOP_DRONE:
		{
			Logging::log("Drone: ", "Stop drone");
			uint8_t* cmd;
			int size = CommandSerializer::serializeCommand(viewCommand, &cmd);
			mCommunication->send(cmd, size);
			break;
		}
		default: break;
	}	
}