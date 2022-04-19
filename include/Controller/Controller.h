#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"Model/Model.h"
#include"View/View.h"
#include"Controller/InputManager.h"


class Controller
{
public:

	Controller();
	void run();

private:

	void startInputManager();
	void startView();

	Model mModel;
	View mView;
	InputManager mInputManager;
};


#endif