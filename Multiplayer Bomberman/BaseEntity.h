#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "Rectangle.h"
#include "maths.h"
#include "types.h"

struct EntityImpl_t;
class Visualisation;

class BaseEntity
{
public:
	virtual ~BaseEntity(void);
	virtual void OnCollision(const BaseEntity *ent) = 0;
	virtual void Update() = 0;
	virtual void Render(const double dt, Visualisation * vis) = 0;
	virtual void DoAnimation() = 0;

	void DropBomb();
	void Move(const math::Vector2& dir);
	
	bool GetActive() const; 
	math::Vector2& GetPosition() const; 	
	int GetID() const;
	int GetGraphicID() const;
	rec::Rectangle& GetCollisionBox() const;
	EntitySide GetSide() const;

	void SetActive(const bool ac);
	void SetID(const int id);
	void SetGraphicID(const int gid);
	void SetCollisionBox(const rec::Rectangle& other);
	void SetPosition(const math::Vector2& position);
	void SetSide(const EntitySide side);

protected:
	BaseEntity(void);
	BaseEntity(const EntityImpl_t& ei);
	
protected:
	EntityImpl_t* impl;
};

#endif
