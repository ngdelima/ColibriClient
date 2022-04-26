#include"Controller/Controller.h"
#include<thread>
#include<chrono>

Controller::Controller()
: mModel()
, mView()
{

}

Controller::~Controller()
{

}

void Controller::run()
{
	startView();
}

void Controller::startView()
{
	mView.run();
}