#include"Model/CommandSerializer.h"
#include"Logging/Logging.h"

int CommandSerializer::serializeCommand(ViewCommand* viewCommand, uint8_t** cmd)
{
	int size = 0;

	switch(viewCommand->mId)
	{
		case VIEW_COMMAND_ID::COMMAND_START_DRONE:
		{
			Logging::log("CommandSerializer", "Start drone");
			*cmd = (uint8_t*)calloc(2, sizeof(uint8_t));
			(*cmd)[0] = COMMAND_START_DRONE_BYTE;
			(*cmd)[1] = '\n';
			size = 2;
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_STOP_DRONE:
		{
			*cmd = (uint8_t*)calloc(2, sizeof(uint8_t));
			(*cmd)[0] = COMMAND_STOP_DRONE_BYTE;
			(*cmd)[1] = '\n';
			size = 2;
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED:
		{
			SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
					dynamic_cast<SetMotorSpeedViewCommand*>(viewCommand);

			*cmd = (uint8_t*)calloc(4, sizeof(uint8_t));
			(*cmd)[0] = COMMAND_SET_MOTOR_SPEED_BYTE;
			(*cmd)[1] = (uint8_t)(setMotorSpeedViewCommand->mMotorId);
			(*cmd)[2] = (uint8_t)(setMotorSpeedViewCommand->mMotorSpeed);
			(*cmd)[3] = '\n';
			size = 4;
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED_DELTA:
		{
			break;
		}
		default: break;
	}
	return size;
}

/*void deserializeMessage()
{

}*/