#include"View/Screen.h"

Screen::Screen(ViewMediator* viewMediator, SDL_Renderer* renderer, std::string title)
: ViewMediatorComponent(viewMediator)
, mRenderer(renderer)
, mTitle(title)
{
	initialize();
}

Screen::~Screen()
{

}

void Screen::initialize()
{
	mViewMediator->setScreenComponent(this);
}