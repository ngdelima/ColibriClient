#ifndef MODEL_H
#define MODEL_H

#include"View/Commands/ViewCommands.h"
#include"Model/Drone.h"

class Model
{
public:

	Model();
	void setViewCommandQueue(ThreadSafeViewCommandQueue* viewCommandQueue)
	{ mViewCommandQueue = viewCommandQueue; }
	void run();

private:

	void modelLoop();
	void executeCommand(ViewCommand* viewCommand);
	
	void startDrone();
	void stopDrone();

	ThreadSafeViewCommandQueue* mViewCommandQueue;

	Drone* mDrone;
	bool mDroneStarted;
};

#endif