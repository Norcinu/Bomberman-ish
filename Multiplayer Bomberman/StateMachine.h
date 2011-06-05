#ifndef ENTITY_STATEMACHINE_H
#define ENTITY_STATEMACHINE_H

#include "State.h"
#include <cassert>

namespace entityFSM 
{
	template <class T>
	class StateMachine
	{
	public:
		StateMachine(T * owner_) : owner(owner_), current_state(nullptr), previous_state(nullptr),
			global_state(nullptr) {}

		virtual ~StateMachine(void)	{}

		void SetCurrentState(State<T> * s)  { current_state = s; }
		void SetGlobalState(State<T> * s)   { global_state = s; }
		void SetPreviousState(State<T> * s) { previous_state = s; }
		
		State<T> * CurrentState()  const { return current_state; }
		State<T> * GlobalState()   const { return global_state; }
		State<T> * PreviousState() const { return previous_state; }
		
		void Update() const
		{
			if (global_state)
				global_state->Execute(owner);

			if (current_state)
				current_state->Execute(owner);
		}
		
		void ChangeState(State<T> * new_state)
		{
			assert(new_state && 
           "<StateMachine::ChangeState>: trying to change to NULL state");

			previous_state = current_state;
			current_state->Exit(owner);
			current_state = new_state;
			current_state->Enter(owner);
		}

		void RevertToPreviousState() { ChangeState(previous_state); }
	
	private:
		T* owner;
		State<T> * current_state;
		State<T> * previous_state;
		State<T> * global_state;
	};
}

#endif
