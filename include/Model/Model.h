#ifndef MODEL_H
#define MODEL_H

#include"View/Commands/ViewCommands.h"
#include"Model/Drone.h"
#include"Logging/Logging.h"

class Model
{
public:

	Model(Communication* communication);
	void setViewCommandQueue(ThreadSafeViewCommandQueue* viewCommandQueue)
	{ mViewCommandQueue = viewCommandQueue; }
	void run();

private:

	void modelLoop();
	void executeCommand(ViewCommand* viewCommand);
	void startDrone();
	
	ThreadSafeViewCommandQueue* mViewCommandQueue;

	Drone* mDrone;
	Communication* mCommunication;

	bool mDroneStarted;
};

#endif