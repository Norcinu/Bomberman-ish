#ifndef MESSAGEEVENT_H
#define MESSAGEEVENT_H

struct EventMessage_t
{
	enum EventType { DROP_BOMB=1, FORWARD, BACK, LEFT, RIGHT, DIE, EXPLOSION };
	
	EventType event_type;
	int id;
	double time_stamp; 
};

#endif
