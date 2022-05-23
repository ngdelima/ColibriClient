#include"Controller/Controller.h"
#include<thread>
#include<chrono>

Controller::Controller()
: mModel(&mCommunication)
, mView()
{

}

Controller::~Controller()
{

}

void Controller::run()
{
	startModel();
	startView();
}

void Controller::startModel()
{
	mModel.setViewCommandQueue(&mViewCommandQueue);
	mModel.run();
}

void Controller::startView()
{
	mView.setViewCommandQueue(&mViewCommandQueue);
	mView.run();
}
