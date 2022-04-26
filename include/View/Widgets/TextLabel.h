#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include"View/Widgets/Widgets.h"

class TextLabel : public Widget
{
public:

	TextLabel(	SDL_Renderer* renderer,
				std::string text,
				int xPos,
				int yPos,
				std::string fontName,
				int fontSize);
	~TextLabel();
	void update() override;
	void render() const override;
	inline void setText(std::string _text) { mText = _text; }
	inline std::string getText() const { return mText; };

private:

	std::string mText;
	std::string mFontName;
	int mFontSize;
};

#endif