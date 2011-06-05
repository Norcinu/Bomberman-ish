#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>

class BaseState;
class Visualisation;
class Menu;
class Events;
class World;
class Messenger;

class Engine
{
public:
	Engine(void);
	~Engine(void);

	bool Initialise();
	void ChangeState(BaseState *state);
	void PushState(BaseState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();
	bool IsRunning () const;

	Events * GetEventManagerPtr() const { return event_manager; }
	Visualisation * GetRendererPtr() const { return renderer; }	
	World * GetWorldModelPtr() const { return world_model; }
	Messenger * GetMessengerPtr() const { return message_system; }

private:
	std::vector<BaseState*> states;
	Events * event_manager;
	Visualisation * renderer;
	World * world_model;
	Messenger * message_system;

	//event
	//menu
	//vis
	//world? - or keep in state.
};

#endif
