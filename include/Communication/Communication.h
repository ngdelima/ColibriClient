#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include"View/Commands/ViewCommands.h"
#include<boost/asio/serial_port.hpp> 
#include<boost/asio.hpp>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>

class CommunicationQueue
{
public:

	void addElement(std::string str)
	{
		mQueueMutex.lock();

		mQueue.push(str);

		mQueueMutex.unlock();
	}

	std::string* getElement()
	{
		std::string* str = nullptr;

		mQueueMutex.lock();

		if(mQueue.size() > 0)
		{
			str = new std::string(mQueue.front());
			mQueue.pop();	
		}

		mQueueMutex.unlock();

		return str;
	}

private:

	std::queue<std::string> mQueue;
	std::mutex mQueueMutex;
};

class Communication
{
public:

	Communication();
	void startDroneCommunication();
	void send(uint8_t* cmd, int lenght);
	bool getReading(std::string* reading);

private:

	std::string read();
	void readLoop();

	boost::asio::io_service mIo;
	boost::asio::serial_port mPort;
	CommunicationQueue mReadQueue;

	
};

#endif