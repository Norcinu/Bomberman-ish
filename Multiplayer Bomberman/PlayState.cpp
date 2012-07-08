#include "PlayState.h"
#include "World.h"
#include "Engine.h"
#include "Events.h"
#include "Visualisation.h"

PlayState PlayState::instance;

PlayState::PlayState(void)
{
}

PlayState::~PlayState(void)
{
}

bool PlayState::Initialise(Engine * eng)
{
	std::cout << "Entering PlayState..." << std::endl;
	if (!eng->GetWorldModelPtr()->Initialise(std::string("data\\levels\\empty.lvl"), eng->GetRendererPtr()))
		return false;

	return true;
}

void PlayState::CleanUp()
{
	std::cout << "Exiting PlayState..." << std::endl;
}

void PlayState::HandleEvent(Engine * eng)
{
	//eng->GetEventManagerPtr()->Update(eng->GetWorldModelPtr());
	eng->GetEventManagerPtr()->Update(eng->GetMessengerPtr());
	
	if (change_state)
		eng->ChangeState(PlayState::GetInstance());
}

void PlayState::Pause()
{

}

void PlayState::Resume()
{

}

void PlayState::Update(Engine * eng)
{
	eng->GetWorldModelPtr()->Update();
}

void PlayState::Render(Engine * eng)
{
	//world->Render(eng->GetRendererPtr());
	eng->GetWorldModelPtr()->Render(eng->GetRendererPtr());
}
