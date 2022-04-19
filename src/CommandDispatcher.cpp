#include"CommandDispatcher.h"

CommandDispatcher::CommandDispatcher()
: mPort(mIo, "/dev/ttyUSB0")
{
	mPort.set_option(boost::asio::serial_port_base::baud_rate(115200));
}

void CommandDispatcher::setMotorSpeedCommand(uint8_t _motorId, uint8_t _speed)
{
	//if (_motorId >= 0x0 && _motorId < 0x1)
	if (_motorId >= 0x0 && _motorId < 0x4)
	{
		uint8_t cmd[4];
		cmd[0] = COMMAND_SET_MOTOR_SPEED;
		cmd[1] = _motorId;
		cmd[2] = _speed;
		cmd[3] = '\n';
		send(cmd, 4);
		std::string response = read();
		std::cout << response << std::endl;
		//if( == (char*)cmd)
		//	std::cout << std::hex << "Sent: " << cmd[0] << cmd[1] << cmd[2] << cmd[3] << "Recieved: " << *(response.c_str()) << std::endl;
	}
}

//TODO: this functino whould be part of a communication module
/*void CommandDispatcher::waitForCommunicationsReady()
{
	while(read() != "DRONE_READY")
	{
		// Put a delay
	}
}*/

void CommandDispatcher::send(uint8_t* cmd, int lenght)
{
	if (lenght > 0)
	{
		boost::asio::write(mPort, boost::asio::buffer(cmd, lenght));
	}
}

std::string CommandDispatcher::read()
{
	std::string response;
	for (;;)
	{
		char c;
		boost::asio::read(mPort, boost::asio::buffer(&c, 1));
		response += c;
		if (c == '\n')
		{
			break;
		}
	}
	return response;
}