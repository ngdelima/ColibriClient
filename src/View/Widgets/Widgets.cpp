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

ClickableWidget::ClickableWidget(	SDL_Renderer* renderer,
									int xPos,
									int yPos,
									int xEndPos,
									int yEndPos,
									std::function<void()> callback)
: Widget(renderer, xPos, yPos)
, mXEndPos(xEndPos)
, mYEndPos(yEndPos)
, mCallback(callback)
{}

bool ClickableWidget::isClicked(int xClickPos, int yClickPos)
{
	// TODO: Check is click is inside area
	return false;
}


void ClickableWidget::onClick()
{
	mCallback();
}

