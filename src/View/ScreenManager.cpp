#include"View/ScreenManager.h"

ScreenManager::ScreenManager(SDL_Window* window, SDL_Renderer* renderer, InputManager* inputManager)
: mCurrentScreen(nullptr)
, mWindow(window)
, mRenderer(renderer)
, mInputManager(inputManager)
{
	initialize();
}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::initialize()
{
	changeScreen(SCREEN_ID::MENU_SCREEN, "Menu Screen");
}

bool ScreenManager::update()
{
	KeyStateArray keyStateArray = mInputManager->getKeyStateArray();
	
	if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ESC)] == INPUT_STATE::PRESSED)
	{
		std::cout << "Pressed escape" << '\n'; // Stop program execution
		return false;
	}

	mCurrentScreen->update(keyStateArray);
	return true;
}

void ScreenManager::render()
{
	mCurrentScreen->render();
}

void ScreenManager::changeScreen(SCREEN_ID screenId, std::string title)
{
	if(mCurrentScreen != nullptr) delete mCurrentScreen;
	ScreenFactory screenFactory;
	mCurrentScreen = screenFactory.createScreen(screenId, mRenderer, title);
	if(mCurrentScreen == nullptr) std::cout << "Null screen" << '\n';
}
