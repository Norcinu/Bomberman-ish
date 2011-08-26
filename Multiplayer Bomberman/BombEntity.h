#ifndef BOMBENTITY_H
#define BOMBENTITY_H

#include "BaseEntity.h"

class Timer;

class BombEntity : public BaseEntity
{
public:
	BombEntity(void);
	BombEntity(const EntityImpl_t& ei);
	~BombEntity(void);

	void OnCollision(const BaseEntity *ent);
	void Update();
	void Render(const double dt, Visualisation * vis);
	void DoAnimation();

private:
	Timer *timer;
};

#endif
