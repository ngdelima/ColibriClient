#include"Model/Model.h"
#include<thread>
#include<iostream>

Model::Model()
{

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
	switch(viewCommand->mId)
	{
		case VIEW_COMMAND_ID::COMMAND_START_DRONE:
		{
			startDrone();
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_SET_MOTOR_SPEED:
		{
			SetMotorSpeedViewCommand* setMotorSpeedViewCommand =
					dynamic_cast<SetMotorSpeedViewCommand*>(viewCommand);
			std::cout << "Model: onViewCommandSent: Set Motor Speed: " 
				<< " MotorId" << (int)setMotorSpeedViewCommand->mMotorId 
				<< " Speed" << setMotorSpeedViewCommand->mMotorSpeed
				<< '\n';
			break;
		}
		case VIEW_COMMAND_ID::COMMAND_STOP_DRONE:
		{
			std::cout << "Model: onViewCommandSent: Stop Drone" << '\n';
			break;
		}
		default: break;
	}	
}

void Model::startDrone()
{
	mDrone = new Drone();
	mDroneStarted = true;
}

void Model::stopDrone()
{
	delete mDrone;
	mDroneStarted = false;
}