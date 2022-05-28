#ifndef COMMAND_SERIALIZER_H
#define COMMAND_SERIALIZER_H

#include"View/Commands/ViewCommands.h"

#define COMMAND_MAX_SIZE 10
#define COMMAND_ID_POSITION		0x0

#define COMMAND_START_DRONE_BYTE 		0x00
#define COMMAND_STOP_DRONE_BYTE 		0x01

#define COMMAND_SET_MOTOR_SPEED_BYTE 	0x02


class CommandSerializer
{
public:

	static int serializeCommand(ViewCommand* viewCommand, uint8_t** cmd);
};

#endif