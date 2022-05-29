#include"Model/Model.h"
#include"ViewModel/ViewModel.h"
#include<thread>

Model::Model(Communication* communication)
: mCommunication(communication)
, mDrone(nullptr)
, mDroneStarted(false)
{
	// TODO: Assert on Comms nullptr
	Logging::log("Model", "Construction");
	if(mCommunication == nullptr) Logging::log("Model", "Null communication");
}

void Model::run()
{
	std::thread modelLoopThread(&Model::modelLoop, this);
	modelLoopThread.detach();
}

void Model::modelLoop()
{
	while(true)
	{
		ViewCommand* viewCommand = mViewCommandQueue->getCommand();
		if(viewCommand != nullptr)
		{
			executeCommand(viewCommand);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void Model::executeCommand(ViewCommand* viewCommand)
{
	Logging::log("Model", "executeCommand");
	if(viewCommand != nullptr)
	{
		if( VIEW_COMMAND_ID::FIRST_DRONE_COMMAND <= viewCommand->mId &&
			viewCommand->mId <= VIEW_COMMAND_ID::LAST_DRONE_COMMAND)
		{
			if(mDroneStarted)
			{
				if(viewCommand->mId == VIEW_COMMAND_ID::COMMAND_SET_VIEW_MODEL_DRONE)
				{
					(dynamic_cast<SetViewModelDroneViewCommand*>(viewCommand)->mViewModel)->setDrone(mDrone);
					(dynamic_cast<SetViewModelDroneViewCommand*>(viewCommand)->mViewModel)->setIsRunning(true);
				}
				else
					mDrone->addCommand(viewCommand);
			}
			else
			{
				startDrone();
			}
		}
	}
}

void Model::startDrone()
{
	mDroneStarted = true;
	mCommunication->startDroneCommunication();
	mDrone = new Drone(mCommunication);
	mDrone->run();
}
