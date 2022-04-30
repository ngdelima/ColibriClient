#include"View/ScreenManager.h"

ScreenManager::ScreenManager(	ViewMediator* viewMediator,
								SDL_Window* window,
								SDL_Renderer* renderer,
								InputManager* inputManager)
: ViewMediatorComponent(viewMediator)
, mCurrentScreen(nullptr)
, mNextScreen(SCREEN_ID::NO_SCREEN)
, mWindow(window)
, mRenderer(renderer)
, mInputManager(inputManager)
{
	// Check nullptrs in members
	initialize();
}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::initialize()
{
	mViewMediator->setScreenManagerComponent(this);
	changeScreen(SCREEN_ID::MENU_SCREEN, "Menu Screen");
}

bool ScreenManager::update()
{
	KeyStateArray keyStateArray = mInputManager->getKeyStateArray();
	
	if(keyStateArray[static_cast<size_t>(KEY_ID::KEY_ESC)] == INPUT_STATE::PRESSED)
	{
		return false;
	}
	
	mCurrentScreen->update(keyStateArray);
	
	if(mNextScreen != SCREEN_ID::NO_SCREEN)
	{
		changeScreen(mNextScreen, "Test");
		
		if(mCurrentScreen == nullptr)
		{
			return false;
		}
	}

	return true;
}

void ScreenManager::render()
{
	mCurrentScreen->render();
}

void ScreenManager::changeScreen(SCREEN_ID screenId, std::string title)
{
	if(mCurrentScreen != nullptr) delete mCurrentScreen;
	mCurrentScreen = ScreenFactory::createScreen(screenId, mRenderer, title, mViewMediator);
	if(mCurrentScreen == nullptr) std::cout << "Null screen" << '\n';
	mNextScreen = SCREEN_ID::NO_SCREEN;
}

void ScreenManager::onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification)
{
	switch(notification)
	{
		case VIEW_NOTIFICATION::SCREEN_NAVIGATE:
		{
			std::cout << "Screen manager: Must navigate" << '\n';
			mNextScreen = mCurrentScreen->getNextScreen();
			break;
		}
		default:
		break;
	}
}