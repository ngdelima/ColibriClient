#include"View/Widgets/MenuTile.h"

MenuTile::MenuTile(	SDL_Renderer* renderer,
					std::string text,
					int xPos,
					int yPos,
					int xEndPos,
					int yEndPos,
					std::string fontName,
					int fontSize,
					std::function<void()> callback)
: ClickableWidget(renderer, xPos, yPos, xEndPos, yEndPos, callback)
, mText(text)
, mFontName(fontName)
, mFontSize(fontSize)
, mIsHighlighted(false)
{
}

MenuTile::~MenuTile()
{
}

void MenuTile::render() const
{
	TTF_Font* font = TTF_OpenFont(mFontName.c_str(), mFontSize);

	if(font == nullptr)
	{
		// TODO: Implement error logging
		return;
	}

	SDL_Color fg = { 255,0,0,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, mText.c_str(), fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(mRenderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = mXPos;
	posRect.y = mYPos;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(mRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void MenuTile::update()
{

}

void MenuTile::setIsHighlighted(bool highlight)
{
	mIsHighlighted = highlight;
	if(mIsHighlighted)
	{
		mText.insert(0, "* ");
	}
	else
	{
		mText.erase(0, 2);
	}
}