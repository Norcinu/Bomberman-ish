#ifndef BOTENTITY_H
#define BOTENTITY_H

#include "baseentity.h"
#include "StateMachine.h"

//class entityFSM::StateMachine<BotEntity>;

class BotEntity : public BaseEntity
{
public:
	BotEntity(void);
	~BotEntity(void);

	void OnCollision(const BaseEntity *ent);
	void Update();
	void Render(const double dt, Visualisation * vis);
	void DoAnimation();

private:
	entityFSM::StateMachine<BotEntity> *state_machine;
};

#endif
