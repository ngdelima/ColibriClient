#include"View/View.h"

#include<thread>

View::View()
: ViewMediatorComponent(nullptr)
, mWindow(nullptr)
, mRenderer(nullptr)
, mScreenManager(nullptr)
, mInputManager(nullptr)
, mViewCommandQueue(nullptr)
{
}

View::~View()
{
	delete mScreenManager;
	delete mInputManager;
}

void View::run()
{
	std::thread viewLoopThread(&View::viewLoop, this);
	viewLoopThread.detach();
}

void View::initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	mWindow = SDL_CreateWindow(
		"Colibri",		                   // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (mWindow == NULL) 
	{
		// TODO: Error logging
		//printf("Could not create window: %s\n", SDL_GetError());
		return;
	}

	if (TTF_Init() == -1)
	{
		// TODO: Error logging
		return;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	// TODO: Error logging mRenderer NULL

	mInputManager = new InputManager();
	if(mInputManager == nullptr)
	{
		// Assert
	}

	mViewMediator = new ViewMediator();
	if(mViewMediator == nullptr)
	{
		// Assert
	}
	mViewMediator->setViewComponent(this);

	mScreenManager = new ScreenManager(mViewMediator, mWindow, mRenderer, mInputManager);
	if(mScreenManager == nullptr)
	{
		// Assert
	}


	// CommandDispatcher commandDispatcher;
	// Drone drone(&commandDispatcher);
	// Screen mainScreen(&drone);
}

void View::deintialize()
{
	TTF_Quit();
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void View::viewLoop()
{
	initialize();
	mInputManager->run();

	float lastFrame = (float)SDL_GetTicks() * 0.001f;
	float currentFrame;
	float elapsedTime;

	SDL_Event event;
	while (SDL_PollEvent(&event) >= 0)
	{
		currentFrame = (float)SDL_GetTicks() * 0.001f;
		elapsedTime = currentFrame - lastFrame;

		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
		SDL_RenderClear(mRenderer);

		if(mScreenManager->update() == false)
		{
			break;
		}
		mScreenManager->render();

		lastFrame = currentFrame;

		SDL_RenderPresent(mRenderer);
		// TODO: Delay depending on fps
		SDL_Delay(10);
	}
	deintialize();
}

void View::onNotify(ViewMediatorComponent* viewMediatorComponent, VIEW_NOTIFICATION notification)
{

}

void View::onViewCommandSent(ViewCommand* viewCommand)
{
	if(viewCommand != nullptr)
	{
		mViewCommandQueue->addCommand(viewCommand);
	}
}