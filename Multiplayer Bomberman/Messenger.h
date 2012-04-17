#ifndef MESSENGER_H
#define MESSENGER_H

#include <deque>
#include "MessageEvent.h"

class Messenger
{
public:
	Messenger(void);
	~Messenger(void);

	void AddMessage(const EventMessage_t& msg);
	void EmptyQueue();
	bool IsEmpty() const { return messages.empty(); }
	EventMessage_t PopFront(); 

private:
	std::deque<EventMessage_t> messages;
};

bool MessageQueueSort(const EventMessage_t& m1, const EventMessage_t& m2);

#endif
