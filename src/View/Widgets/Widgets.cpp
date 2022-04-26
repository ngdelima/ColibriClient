#include"View/Widgets/Widgets.h"

Widget::Widget( SDL_Renderer* renderer,
				int xPos,
				int yPos)
: mRenderer(renderer)
, mXPos(xPos)
, mYPos(yPos)
{}

Widget::~Widget()
{}