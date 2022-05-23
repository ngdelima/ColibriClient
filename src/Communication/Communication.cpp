#include"Communication/Communication.h"
#include"Logging/Logging.h"

Communication::Communication()
: mPort(mIo, "/dev/ttyUSB0")
{
	mPort.set_option(boost::asio::serial_port_base::baud_rate(115200));
}

void Communication::startDroneCommunication()
{
	std::thread communicationLoopThread(&Communication::readLoop, this);
	communicationLoopThread.detach();
}

void Communication::send(uint8_t* cmd, int lenght)
{
	Logging::log("Communication", "Send");
	if (lenght > 0)
	{
		boost::asio::write(mPort, boost::asio::buffer(cmd, lenght));
	}
}

std::string Communication::read()
{
	std::string response;
	for (;;)
	{
		char c;
		boost::asio::read(mPort, boost::asio::buffer(&c, 1));
		if (c == '\n')
		{
			Logging::log("CommunicationRead", response);
			break;
		}
		else
		{
			response += c;
		}
	}
	return response;
}

void Communication::readLoop()
{
	while(true)
	{
		mReadQueue.addElement(read());
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

bool Communication::getReading(std::string* reading)
{
	reading = mReadQueue.getElement();
	return (reading != nullptr);
}