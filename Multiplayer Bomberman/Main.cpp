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
#include "Common.h"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <json/json.h>

int main(int argc, char *argv[])
{
    json_object * str = json_object_new_string("cunt\n");
    std::cout << "My string is " << json_object_get_string(str);
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "Current Path: " << path << std::endl;
#endif
#ifdef _DEBUG
#ifdef __LINUX__ // !!!! MOVE THIS TO MAIN STARTUP !!!!
	const std::string delim = "/"
#else
	const std::string delim = "\\";
#endif // __LINUX__
	std::string log_file = "Logfiles" + delim + "tiles.txt";
	LOG_SET_FILENAME(log_file.c_str());
#endif // _DEBUG
    std::cout << getwd << std::endl;
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
