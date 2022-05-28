#ifndef DRONE_H
#define DRONE_H

#include"Communication/Communication.h"
#include"View/Commands/ViewCommands.h"
#include"Model/CommandSerializer.h"
#include"Logging/Logging.h"
#include<map>

class Drone
{
public:

	Drone(Communication* communication);

	void run();
	void addCommand(ViewCommand* viewCommand);

private:

	bool start();
	bool connect();

	std::map<MOTOR_ID, int> mMotorSpeeds;

	Communication* mCommunication;
	std::queue<std::string> mRecievedQueue;

	bool mDroneIsRunning;
	bool mDroneIsConnected;

};

#endif