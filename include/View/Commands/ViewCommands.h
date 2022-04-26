#ifndef VIEW_COMMANDS_H
#define VIEW_COMMANDS_H

#include"View/ScreenId.h"

class ViewCommand
{
public:

	virtual void execute() = 0;
};

class NavigateCommand : public ViewCommand
{
public:
	
	NavigateCommand(SCREEN_ID screenId)
	: mScreenId(screenId)
	{}

	void execute() override
	{

	}

	SCREEN_ID mScreenId;
};

class ViewCommandMediator
{
	
};


#endif