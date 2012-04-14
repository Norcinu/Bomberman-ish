#include "Engine.h"
#include "Events.h"
#include "Visualisation.h"
#include "BaseState.h"
#include "World.h"
#include "Messenger.h"

Engine::Engine(void) : 
	renderer(nullptr), 
	event_manager(nullptr), 
	world_model(nullptr), 
	message_system(nullptr)
{
	states.reserve(4);
}

Engine::~Engine(void)
{
	delete event_manager;
	delete world_model;
	delete renderer;
	delete message_system;
}

bool Engine::Initialise()
{
	event_manager = new Events;
	renderer = new Visualisation;
	
	if (!renderer->Initialise(480, 640))
		return false;
	
	message_system = new Messenger;
	world_model = new World(message_system);
	
	return true;
}

void Engine::PushState(BaseState* state)
{
	if (!states.empty())
		states.back()->Pause();

	states.push_back(state);
	states.back()->Initialise(this);
}

void Engine::PopState()
{
	if (!states.empty())
	{
		states.back()->CleanUp();
		states.pop_back();
	}

	if (!states.empty())
		states.back()->Resume();
}

void Engine::ChangeState(BaseState * state)
{
	if (!states.empty())
	{
		states.back()->CleanUp();
		states.pop_back();
	}

	if (!message_system->IsEmpty())
		message_system->EmptyQueue();

	if (!renderer->IsEmpty())
		renderer->ClearGraphicSet();

	states.push_back(state);
	if (!states.back()->Initialise(this))
	{
		printf("Error loading game state. Application is Exiting...\n");
		event_manager->Running(false);
	}
}

bool Engine::IsRunning() const
{
	return event_manager->Running();
}

void Engine::HandleEvents()
{
	//event_manager->Update(world_model);
	states.back()->HandleEvent(this);
}

void Engine::Update()
{
	states.back()->Update(this);
}

// turn on /GM flag if turning off /MP
void Engine::Render()
{
	//world_model->Render(renderer);
	states.back()->Render(this);
	
}
