#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include"SDL2/SDL.h"
#include"Listener.h"
#include"InputEvent.h"
#include"InputMap.h"

#include<thread>
#include<chrono>
#include<vector>
#include<map>
#include<mutex>
#include<algorithm>

class InputManager
{
public:

	InputManager()
	{
		for(size_t keyId = static_cast<size_t>(KEY_ID::KEY_FIRST); 
			keyId != static_cast<size_t>(KEY_ID::KEY_LAST);
			++keyId)
		{
			mKeyStateArray[static_cast<size_t>(keyId)] = INPUT_STATE::NOT_PRESSED;
		}
	}

	void run() 
	{
		std::thread inputLoopThread(&InputManager::inputLoop, this);
		inputLoopThread.detach();
	}

	KeyStateArray getKeyStateArray()
	{
		// At this moment I'll just make a copy, 
		// I don't know how to pass a thread safe reference
		KeyStateArray v;

		mKeyStateArrayMutex.lock();

		//std::copy(mKeyStateArray, mKeyStateArray.begin() + mKeyStateArray.size(), v.begin());
		v = mKeyStateArray;

		mKeyStateArrayMutex.unlock();

		return v;
	}

private:
	
	KeyStateArray mKeyStateArray;
	std::mutex mKeyStateArrayMutex;

	void inputLoop()
	{
		while (true)
		{
			mKeyStateArrayMutex.lock();

			const Uint8* keystate = SDL_GetKeyboardState(NULL);

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ESC)] =	
						(keystate[SDL_SCANCODE_ESCAPE]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ENTER)] =	
						(keystate[SDL_SCANCODE_RETURN]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_W)] =
						(keystate[SDL_SCANCODE_W]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_A)] =
						(keystate[SDL_SCANCODE_A]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_S)] =
						(keystate[SDL_SCANCODE_S]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_D)] =
						(keystate[SDL_SCANCODE_D]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_UP)] =
						(keystate[SDL_SCANCODE_UP]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_DOWN)] =
						(keystate[SDL_SCANCODE_DOWN]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_LEFT)] =
						(keystate[SDL_SCANCODE_LEFT]) ? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArray[static_cast<size_t>(KEY_ID::KEY_ARROW_RIGHT)] =
						(keystate[SDL_SCANCODE_RIGHT])? INPUT_STATE::PRESSED : INPUT_STATE::NOT_PRESSED;

			mKeyStateArrayMutex.unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

};

#endif