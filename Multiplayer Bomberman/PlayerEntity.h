#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "baseentity.h"
#include <vector>

class PlayerEntity : public BaseEntity
{
public:
	PlayerEntity(void);
	PlayerEntity(const EntityImpl_t& ei);
	~PlayerEntity(void);

	void Update();
	void Render(const double dt, Visualisation * vis);
	void OnCollision(const BaseEntity *ent);
	void DoAnimation();
};

#endif

