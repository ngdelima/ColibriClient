#pragma once

#include"SDL/SDL.h"
#include"SDL/SDL_rect.h"
//#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"

#include"Drone.h"

#include<iostream>
#include<sstream>
#include<string>

class TextLabel
{
public:
	TextLabel(std::string _text, int _xPos, int _yPos, std::string _fontName, int _fontSize)
	: mText(_text)
	, mXPos(_xPos)
	, mYPos(_yPos)
	, mFontName(_fontName)
	, mFontSize(_fontSize)
	{
	}

	void render(SDL_Renderer* renderer) 
	{
		TTF_Font* font = TTF_OpenFont(mFontName.c_str(), mFontSize);

		SDL_Color fg = { 255,0,0,255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, mText.c_str(), fg);

		SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

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

		SDL_RenderCopy(renderer, optimizedSurface, &sizeRect, &posRect);
		SDL_DestroyTexture(optimizedSurface);
		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
	}

	void setText(std::string _text) { mText = _text; }
	std::string getText() { return mText; }

private:

	std::string mText;
	int mXPos;
	int mYPos;
	std::string mFontName;
	int mFontSize;
};

class MotorIndicator
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

};

class Screen
{
public:

	Screen(Drone* _drone)
	: mDrone(_drone)
	{
		if (mDrone == nullptr)
			return;

		mMotor1Indicator = new MotorIndicator(mDrone->getMotor1(), "1", 0, 0, 0, ".\\FreeMono.ttf", 24);
		mMotor2Indicator = new MotorIndicator(mDrone->getMotor2(), "2", 0, 0, 100, ".\\FreeMono.ttf", 24);
		mMotor3Indicator = new MotorIndicator(mDrone->getMotor3(), "3", 0, 0, 200, ".\\FreeMono.ttf", 24);
		mMotor4Indicator = new MotorIndicator(mDrone->getMotor4(), "4", 0, 0, 300, ".\\FreeMono.ttf", 24);
	}

	bool update()
	{
		mMotor1Indicator->update();
		mMotor2Indicator->update();
		mMotor3Indicator->update();
		mMotor4Indicator->update();

		return true;
	}

	void render(SDL_Renderer* renderer)
	{
		mMotor1Indicator->render(renderer);
		mMotor2Indicator->render(renderer);
		mMotor3Indicator->render(renderer);
		mMotor4Indicator->render(renderer);
	}

private:

	Drone* mDrone;

	MotorIndicator* mMotor1Indicator;
	MotorIndicator* mMotor2Indicator;
	MotorIndicator* mMotor3Indicator;
	MotorIndicator* mMotor4Indicator;

};
