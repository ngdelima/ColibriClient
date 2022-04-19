#include"Controller/Controller.h"
#include<thread>
#include<chrono>

Controller::Controller(): mModel()
						, mView()
						, mInputManager()
{

}

void Controller::run()
{
	startView();
}

void Controller::startInputManager()
{
	mInputManager.run();
}

void Controller::startView()
{
	mView.run();
}