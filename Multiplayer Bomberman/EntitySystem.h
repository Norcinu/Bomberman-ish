#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <map>
#include <vector>
#include "maths.h"

typedef int FamilyId;
struct EntitySystem;

struct Component 
{
};

struct Entity 
{
	static EntitySystem *entity_system;
	Entity();
	
	template<typename Type>
	Type *GetAs();
	
	std::map<FamilyId, Component*> m_components;
};

//EntitySystem *Entity::entity_system = 0;

struct EntitySystem 
{
   EntitySystem() 
   { 
	   Entity::entity_system = this; 
   }
   
   template<typename T> 
   T *GetComponent(Entity * e) 
   {
      return (T*)e->m_components[T::familyId];
   }
   
   template<typename T>
   void GetEntities(std::vector<Entity*>& result) 
   {
      auto iterPair = m_componentStore.equal_range(T::familyId);
      for(auto iter = iterPair.first; iter != iterPair.second; ++iter) 
	  {
         result.push_back(iter->second);
      }
   }

   template<typename T> 
   void AddComponent(Entity * e, T * comp) 
   {
      m_componentStore.insert(std::pair<FamilyId, Entity*>(T::familyId, e));
      e->m_components.insert(std::pair<FamilyId, Component*>(T::familyId, comp));
   }

   void DeleteEntity(Entity * e) 
   {
      //Scan Entity Components and get familyIds, then I know what to delete in the ComponentStore
	   delete e;
   }

protected:
   std::multimap<FamilyId, Entity*> m_componentStore;
};


//Entity::Entity() 
//{
//}

template<typename Type> 
Type* Entity::GetAs() 
{
   return entity_system->GetComponent<Type>(this);
}



#include "StateMachine.h"
#include "AStar.h"

//class entityFSM::StateMachine<Entity*>;
//class entityFSM::StateMachine<Entity>

struct Position2D : public Component 
{
	static const FamilyId familyId = 0;
	math::Vector2 position;
	math::Vector2 previous_position;

	//void Update();
};

struct EntityExplosion : public Component
{
	static const FamilyId familyId = 1;
};

struct MyFSM : public Component
{
	static const FamilyId familyId = 2;
	entityFSM::StateMachine<Entity> *state_machine;	
};

struct Collision : public Component
{
	static const FamilyId familyId = 3;
	int health;
	int damage_to_give;
	Collision() : health(100), damage_to_give(5) {}
	Collision(int dmg) : health(100), damage_to_give(dmg) {}
};

struct Drawable : public Component
{
	static const FamilyId familyId = 4;
};

struct Pathfinder : public Component
{
	static const FamilyId familyId = 5;
	AStar * astar_pathfinder;
};

#endif
