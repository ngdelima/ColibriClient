#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"Model/Model.h"
#include"View/View.h"

class Controller
{
public:

	Controller();
	~Controller();
	void run();

private:
	
	void startView();

	Model mModel;
	View mView;
};


#endif