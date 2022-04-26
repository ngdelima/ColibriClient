#ifndef WIDGETS_H
#define WIDGETS_H

#include"SDL2/SDL.h"
#include"SDL2/SDL_rect.h"
//#include"SDL/SDL_image.h"
#include"SDL2/SDL_ttf.h"

#include<string>

class Widget
{
public:

	Widget(SDL_Renderer* renderer, int xPos, int yPos);
	virtual ~Widget();
	virtual void update() = 0;
	virtual void render() const = 0;

protected:

	SDL_Renderer* mRenderer;
	int mXPos;
	int mYPos;
};

/*class MotorIndicator
{
public:

	MotorIndicator(Motor* _motor,std::string _name, int _value, int _xPos, int _yPos, std::string _fontName, int _fontSize)
	: mMotor(_motor)
	, mName(_name)
	, mValue(_value)
	{
		mLabel = new TextLabel(getLabel(_name, _value), _xPos, _yPos, _fontName, _fontSize);
	}

	void update() 
	{
		mLabel->setText(getLabel());
	}

	void render(SDL_Renderer* renderer)
	{
		mValue = mMotor->getSpeed();
		mLabel->render(renderer);
	}

	void addValue(int _value)
	{
		mValue += _value;
		if (mValue > 100)
		{
			mValue = 100;
		} 
		else if (mValue < 0)
		{
			mValue = 0;
		}
	}

private:

	std::string getLabel(std::string _name, int _value)
	{
		std::stringstream label;
		label << "Motor ";
		label << _name;
		label << ": ";
		label << _value;
		label << " %";

		return label.str();
	}

	std::string getLabel()
	{
		return getLabel(mName, mValue);
	}

	Motor* mMotor;

	std::string mName;
	int mValue;
	TextLabel* mLabel;

};*/

#endif