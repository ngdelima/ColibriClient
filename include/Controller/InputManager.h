#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include"SDL2/SDL.h"
#include"Listener.h"
#include"InputEvent.h"

#include<thread>
#include<chrono>
#include<vector>
#include<algorithm>
#include<iostream>

class InputManager : public Publisher
{
public:
	// TODO: Make this a singleton

	static InputManager* getInputManager() 
	{
		if (mInputManager == nullptr)
		{
			mInputManager = new InputManager();
		}
		return mInputManager;
	}

	InputManager() {}

	void run() 
	{
		std::thread inputLoopThread(&InputManager::inputLoop, this);
		inputLoopThread.detach();
	}

	void addListener(Listener* _listener) 
	{
		if (_listener != nullptr)
		{
			mListeners.push_back(_listener);
		}
	}

	void notify(INPUT_EVENT _event)
	{
		for_each(mListeners.begin(), mListeners.end(), 
			[&](Listener* l) 
			{ 
				if (l != nullptr)
				{
					l->onNotify(_event);
				}
			});
	}

private:
	
	static InputManager* mInputManager;
	std::vector<Listener*> mListeners;

	void inputLoop()
	{
		while (true)
		{
			const Uint8* keystate = SDL_GetKeyboardState(NULL);

			if (keystate[SDL_SCANCODE_W])
				notify(INPUT_EVENT::INPUT_EVENT_LEFT_STICK_UP);
			if (keystate[SDL_SCANCODE_S])
				notify(INPUT_EVENT::INPUT_EVENT_LEFT_STICK_DOWN);
			if (keystate[SDL_SCANCODE_D])
				notify(INPUT_EVENT::INPUT_EVENT_LEFT_STICK_RIGHT);
			if (keystate[SDL_SCANCODE_A])
				notify(INPUT_EVENT::INPUT_EVENT_LEFT_STICK_LEFT);
			if (keystate[SDL_SCANCODE_UP])
				notify(INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_UP);
			if (keystate[SDL_SCANCODE_DOWN])
				notify(INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_DOWN);
			if (keystate[SDL_SCANCODE_RIGHT])
				notify(INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_RIGHT);
			if (keystate[SDL_SCANCODE_LEFT])
				notify(INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_LEFT);
			if (keystate[SDL_SCANCODE_ESCAPE])
				notify(INPUT_EVENT::INPUT_EVENT_FULL_STOP);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

};

#endif