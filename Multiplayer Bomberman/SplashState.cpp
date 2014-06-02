#include "SplashState.h"
#include "Engine.h"
#include "Visualisation.h"
#include "Timer.h"
#include "World.h"
#include "Events.h"
#include "PlayState.h"
#include "MenuState.h"

#include <string>

SplashState SplashState::instance;

SplashState::SplashState(void) : running_timer(nullptr), splash_sprite_id(0), splash_run_time(2)
{
}

SplashState::~SplashState(void)
{
}

bool SplashState::Initialise(Engine * eng)
{
	std::cout << "Entering SplashState..." << std::endl;

	if (!eng->GetRendererPtr()->AddSprite(&splash_sprite_id, std::string("data/bitmaps/splash.spr")))
		return false;

	running_timer = new Timer;

	return true;
}

void SplashState::CleanUp()
{
	if (running_timer != nullptr)
		delete running_timer;

	std::cout << "Exiting SplashState..." << std::endl;
}

void SplashState::HandleEvent(Engine * eng)
{
	//eng->GetEventManagerPtr()->Update(eng->GetWorldModelPtr());
	eng->GetEventManagerPtr()->Update(eng->GetMessengerPtr());

    if (change_state) //eng->ChangeState(MenuState::GetInstance());
		eng->ChangeState(PlayState::GetInstance());
}

void SplashState::Update(Engine * eng)
{
    auto seconds = running_timer->Seconds();
	if (seconds > splash_run_time)
		change_state = true;
}

void SplashState::Render(Engine * eng)
{
    math::Vector2 mac(0,0);
	eng->GetRendererPtr()->BeginScene();
	eng->GetRendererPtr()->DrawSprite(splash_sprite_id, mac, mac);
	eng->GetRendererPtr()->EndScene();
}

void SplashState::Pause()
{

}

void SplashState::Resume()
{

}
