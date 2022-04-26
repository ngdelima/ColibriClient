#include"Controller/Controller.h"

#include<thread>
#include<chrono>

int main(int argc, char* args[])
{
	Controller mController;
	mController.run();

	while(true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}