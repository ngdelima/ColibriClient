#include"View/ViewMediator.h"

ViewMediator::ViewMediator(){}
ViewMediator::~ViewMediator(){}

void ViewMediator::notify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification)
{
	if(viewMediatorComponent == nullptr)
	{
		return;
	}
	
	mScreenComponent->onNotify(viewMediatorComponent, notification);
	mScreenManagerComponent->onNotify(viewMediatorComponent, notification);
	mViewComponent->onNotify(viewMediatorComponent, notification);
}

void ViewMediator::sendViewCommand(ViewCommand* viewCommand)
{
	mViewComponent->onViewCommandSent(viewCommand);
}