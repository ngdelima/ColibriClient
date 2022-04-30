#ifndef MENU_TILE_H
#define MENU_TILE_H

#include"View/Widgets/Widgets.h"
#include<functional>

class MenuTile : public ClickableWidget
{
public:

	MenuTile(	SDL_Renderer* renderer,
				std::string text,
				int xPos,
				int yPos,
				int xEndPos,
				int yEndPos,
				std::string fontName,
				int fontSize,
				std::function<void()> callback);
	~MenuTile();
	void update() override;
	void render() const override;
	inline void setText(std::string _text) { mText = _text; }
	inline std::string getText() const { return mText; };
	void setIsHighlighted(bool highlight);

private:

	std::string mText;
	std::string mFontName;
	int mFontSize;
	bool mIsHighlighted;
};

#endif