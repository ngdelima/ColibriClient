#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include<iostream>
#include<boost/asio/serial_port.hpp> 
#include<boost/asio.hpp> 

#include<vector>

#define COMMAND_MAX_SIZE 10
#define COMMAND_ID_POSITION		0x0

#define COMMAND_START_DRONE 		0x00
#define COMMAND_STOP_DRONE 			0x01

#define COMMAND_SET_MOTOR_SPEED 	0x02

class CommandDispatcher
{
public:

	CommandDispatcher()
	: mPort(mIo, "/dev/ttyUSB0")
	{
		mPort.set_option(boost::asio::serial_port_base::baud_rate(115200));
	}
	
	void setMotorSpeedCommand(uint8_t _motorId, uint8_t _speed)
	{
		if (_motorId >= 0x0 && _motorId < 0x4)
		{
			uint8_t cmd[4];
			cmd[0] = COMMAND_SET_MOTOR_SPEED;
			cmd[1] = _motorId;
			cmd[2] = _speed;
			cmd[3] = '\n';
			send(cmd, 4);
			read();
		}
	}

private:

	boost::asio::io_service mIo;
	boost::asio::serial_port mPort;

	void send(uint8_t* cmd, int lenght)
	{
		if (lenght > 0)
		{
			boost::asio::write(mPort, boost::asio::buffer(cmd, lenght));
		}
	}

	void read()
	{
		std::string response;
		for (;;)
		{
			char c;
			boost::asio::read(mPort, boost::asio::buffer(&c, 1));
			response += c;
			if (c == '\n')
			{
				std::cout << response << std::endl;
				break;
			}
		}
	}

};


int stringToCmd(std::string& str, unsigned char** cmd)
{
	int lenght = str.size();

	switch (str[0])
	{
	case '0':
	{
		lenght = 2;
		*cmd = (uint8_t*)malloc(lenght);
		if (*cmd != nullptr)
		{
			(*cmd)[0] = COMMAND_START_DRONE;
			(*cmd)[1] = '\n';
		}
		break;
	}
	case '1':
	{
		lenght = 2;
		*cmd = new uint8_t[lenght];
		(*cmd)[0] = COMMAND_STOP_DRONE;
		(*cmd)[1] = '\n';
		break;
	}
	case '2':
	{
		lenght = 0;
		if (str.size() == 2)
		{

		}
		break;
	}
	default:
	{
		lenght = 0;
		break;
	}
	}
	return lenght;
}

#endif