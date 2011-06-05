#include "Messenger.h"
#include <algorithm>

bool MessageQueueSort(const EventMessage_t& m1, const EventMessage_t& m2)
{
	return m1.time_stamp > m2.time_stamp;
}

Messenger::Messenger(void)
{
}

Messenger::~Messenger(void)
{
}

void Messenger::AddMessage(const EventMessage_t& msg)
{
	messages.push_back(msg);
	std::sort(messages.begin(), messages.end(), MessageQueueSort);	
}

void Messenger::EmptyQueue() 
{
	if (!messages.empty())
	{
		while (!messages.empty())
		{
			messages.pop_front();
		}
	}
}

EventMessage_t& Messenger::PopFront()
{
	EventMessage_t temp = messages.front();
	messages.pop_front();
	return temp;
}