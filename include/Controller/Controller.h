#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"Model/Model.h"
#include"View/View.h"
#include"View/Commands/ViewCommands.h"

class Controller
{
public:

	Controller();
	~Controller();
	void run();

private:

	void startModel();	
	void startView();

	Model mModel;
	View mView;
	ThreadSafeViewCommandQueue mViewCommandQueue;
};



#endif