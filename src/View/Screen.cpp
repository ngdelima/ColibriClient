#include"View/Screen.h"

Screen::Screen(SDL_Renderer* renderer, std::string title)
: mRenderer(renderer)
, mTitle(title)
{
	initialize();
}

Screen::~Screen()
{

}

void Screen::initialize()
{
}