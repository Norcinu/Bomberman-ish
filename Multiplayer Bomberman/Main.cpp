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

int main(int argc, char *argv[])
{
	//Engine *engine = new Engine;
	//std::shared_ptr<Engine> engine(new Engine);
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

	//delete engine;
	return 0;
}

//int main(int argc, char *argv[])
//{
//	try
//	{
//		Visualisation *vis=new Visualisation;
//		if (vis == nullptr)
//			return -2;
//		
//		if (!vis->Initialise(480, 640))
//			printf ("error");
//	
//		World *world=new World;
//		if (world == nullptr)
//			return -3;
//	
//		if (!world->Initialise(std::string("data\\levels\\level1.lvl"), vis))
//			return -4;
//	
//		//BitmapFont *font=new BitmapFont;
//		//font->Initialise("data\\bitmaps\\verdana.bmp");
//			
//		Events *event_manager = new Events;
//		//event_manager->SetKeyMap();
//		while (event_manager->Running())
//		{
//			event_manager->Update(/*world*/);
//			world->Update();
//			world->Render(vis);
//			//font->DrawString(1,1,std::string("Hello, World!"), vis->GetScreenSurface());
//		}
//	
//		delete world;
//		//delete font;
//		delete event_manager;
//		delete vis;
//	}
//	catch (std::bad_alloc& e)
//	{
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}
