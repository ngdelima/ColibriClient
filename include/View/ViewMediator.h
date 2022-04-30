#ifndef VIEW_MEDIATOR_H
#define VIEW_MEDIATOR_H

enum class VIEW_NOTIFICATION
{
	FIRST = 0,
	FULL_PROGRAM_STOP = FIRST,
	SCREEN_NAVIGATE,
	MODEL_COMMAND,
	LAST = MODEL_COMMAND,

};

class ViewMediatorComponent;

class ViewMediator
{
public:

	ViewMediator();
	~ViewMediator();

	void notify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification);
	void setViewComponent(ViewMediatorComponent* viewComponent)
	{ mViewComponent = viewComponent; }
	void setScreenManagerComponent(ViewMediatorComponent* screenManagerComponent)
	{ mScreenManagerComponent = screenManagerComponent; }
	void setScreenComponent(ViewMediatorComponent* screenComponent)
	{ mScreenComponent = screenComponent; }

protected:

	ViewMediatorComponent* mViewComponent;
	ViewMediatorComponent* mScreenManagerComponent;
	ViewMediatorComponent* mScreenComponent;

};

class ViewMediatorComponent
{
public:

	ViewMediatorComponent(ViewMediator* viewMediator) : mViewMediator(viewMediator)
	{}

	virtual void onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification) = 0;

	//void setMediator(ViewMediator* viewMediator) { mViewMediator = viewMediator; }

protected:

	ViewMediator* mViewMediator;
};

#endif