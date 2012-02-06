#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include <map>
#include "maths.h"
#include "MessageEvent.h"
#include <boost\timer.hpp>

const int NUM_OF_KEYS = 10;

class World;
class Messenger;

class Events
{
public:
	Events(void);
	~Events(void);

	void Running(bool r) { running = r; }
	bool Running() const { return running; }
	//void Update(World * world);
	void Update(Messenger * msg);

	void SetKeyMap();

	enum INPUT_EVENTS
	{
		EVT_FORWARD,
		EVT_BACKWARD,
		EVT_RIGHT,
		EVT_LEFT,
		EVT_ACTION,
		EVT_TOGGLE_SOUND_STREAM,
		EVT_VOLUME_UP,
		EVT_VOLUME_DOWN,
		EVT_NEXT_SONG,
		EVT_PREVIOUS_SONG
	};

private:
	void FillMessage(EventMessage_t *out, const int id, const EventMessage_t::EventType ev);

private:
	bool running;
	bool key_table[NUM_OF_KEYS];
	std::map<char, INPUT_EVENTS> keymapping;
	SDL_Event event;
	boost::timer my_timer;
};

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void update();
   
    enum InputType { KEYBOARD = 1, MOUSE, CONTROLLER, AI };
private:
    // DEVICE TYPE. Register user or AI
};

class InputDeviceBase
{
public:
    virtual void update() = 0;
    virtual ~InputDeviceBase() {}

   int entity_to_control;
    
    const int getRegisteredEntity() const { return entity_to_control; }
    void setRegisteredEntity(const int val) { entity_to_control = val; }

private:
    InputDeviceBase() : entity_to_control(0) {}
    
};

//class Keyboard : public InputDeviceBase
//{
//public:
//    Keyboard() {}
//    ~Keyboard() {}
//
//    void update() {}
//
//private:
//};
//
//class Mouse : public InputDeviceBase
//{
//
//};
//
//class Controller : public InputDeviceBase
//{
//
//};
#endif
