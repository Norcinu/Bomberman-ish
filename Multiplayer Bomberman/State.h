#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H

namespace entityFSM
{
	template <class T>
	class State
	{
	public:
		State(void) {}
		virtual ~State(void) {}

		virtual void Enter(T * state) = 0;
		virtual void Execute(T * state) = 0;
		virtual void Exit(T * state) = 0;
	};
}
#endif
