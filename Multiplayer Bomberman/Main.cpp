#include <iostream>

#include "Visualisation.h"
#include "BitmapFont.h"
#include "Level.h"
#include "World.h"
#include "Events.h"

#include "Profiler.h"
#include <string>

#include "Engine.h"
#include "SplashState.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
#ifdef _DEBUG
#ifdef __LINUX__ // !!!! MOVE THIS TO MAIN STARTUP !!!!
	const std::string delim = "//"
#else
	const std::string delim = "\\";
#endif // __LINUX__
	std::string log_file = "Logfiles" + delim + "tiles.txt";
	LOG_SET_FILENAME(log_file.c_str());
#endif // _DEBUG

	Engine engine;
	if (!engine.Initialise())
		return -1;

	engine.ChangeState(SplashState::GetInstance());

    while (engine.IsRunning())
	{
		engine.HandleEvents();
		engine.Update();
		engine.Render();
	}

#ifdef _DEBUG
	LOG_WRITE_FILE;
#endif

	return 0;
}
