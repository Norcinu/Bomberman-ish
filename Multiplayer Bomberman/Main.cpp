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
#include "FastDelegate\FastDelegate.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
	Engine engine;
	if (!engine.Initialise())
		return -1;
   
    /*LOG_WRITE_TO_STDIO("fuck off");
    LOG_SET_FILENAME("test1.txt");
    LOG_APPEND("TEST 1");
    LOG_APPEND("TEST 2");
    LOG_WRITE_FILE;*/

	engine.ChangeState(SplashState::GetInstance());

    while (engine.IsRunning())
	{
		engine.HandleEvents();
		engine.Update();
		engine.Render();
	}

	return 0;
}
