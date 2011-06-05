#include "World.h"
#include "Visualisation.h"
#include "Timer.h"
#include "Level.h"
#include "EntityImpl.h"
#include "BaseEntity.h"
#include "PlayerEntity.h"
#include "BombEntity.h"
#include "Explosion.h"
#include "maths.h"
#include "Messenger.h"
#include "EntitySystem.h"

#include <algorithm>
#include <fstream>
#include <boost\bind.hpp>

EntitySystem entity_system;
Entity game_entities[MAX_PLAYERS];

World::World(void) : game_timer(new Timer), current_level(nullptr), update_delta(0.0), tick_rate(50)
{
	entities.reserve(MAX_PLAYERS);
	spawns.reserve(MAX_SPAWNPOINTS);
	bomb_list.reserve(MAX_BOMBS);
	explosion_list.reserve(NUM_EXPLOSIONS);

	//entity_system = new EntitySystem;
	//game_entities = new Entity[MAX_PLAYERS];
}

World::World(Messenger * msg) : game_timer(new Timer), current_level(nullptr), update_delta(0.0), tick_rate(50),
	messages(msg)
{
}

World::~World(void)
{
	CleanUp();
}

bool World::Initialise(const std::string& assets, Visualisation * vis)
{
	std::cout << "world->init";
	current_level = new Level;//(32, 32, 20, 15);
	if (current_level == nullptr)
		return false;

	int gid1 = 0;
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\brick.spr")))
		return false;

	int gid2 = 0;
	if (!vis->AddSprite(&gid2, std::string("data\\bitmaps\\destroyable_brick.spr")))
		return false;
	
	if (!current_level->LoadData(assets, gid1, gid2))
		return false;

	current_level->GetSpawnPoints(spawns);
	
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\sprite.spr")))
		return false;

	AddPlayer(gid1);
	AddPlayer(gid1);
	AddPlayer(gid1);
	AddPlayer(gid1);
	
	if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\bomb.spr")))
		return false;
	
	CreateBombList(gid1);

	//if (!vis->AddSprite(&gid1, std::string("data\\bitmaps\\explosion.spr")))
		//return false;

	return true;
}

void World::CleanUp()
{
	for (ent_itor it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	for (bomb_itor it = bomb_list.begin(); it != bomb_list.end(); ++it)
		delete *it;

	for (explosion_itor it = explosion_list.begin(); it != explosion_list.end(); it)
		delete *it;

	if (game_timer != nullptr)
		delete game_timer;

	if (current_level != nullptr)
		delete current_level;
}

bool World::IsCollideable(const BaseEntity* ent1, const BaseEntity* ent2) const
{
	return true;
}

bool World::CheckBounds(const int id) const
{
	if (id < 0 && id > (int)entities.size()-1)
		return false;
	else
		return true;
}
void World::Move(const int id, const math::Vector2& direction)
{
	// when a bomb explodes and destroys a wall, this wall must be reset
	// in the level copy and id set so it can become a walkable area.
	if (CheckBounds(id)) 
	{
		entities[id]->Move(direction);
		entities[id]->DoAnimation();
#ifdef _DEBUG
		std::cout << "position : " << entities[id]->GetPosition() << std::endl;
#endif
	}
}

void World::Action(const int id)
{
	if (CheckBounds(id))
	{
		for(size_t i = 0; i<bomb_list.size(); ++i)
		{
			if (!bomb_list[i]->GetActive())
			{
				bomb_list[i]->SetActive(true);
				bomb_list[i]->SetPosition(entities[id]->GetPosition());
				bomb_list[i]->SetSide(entities[id]->GetSide());
				break;
			}
		}
	}
	// explosions go 4 up, down, left and right unless they hit something.
		//entities[id]->DropBomb(); // not sure this is needed.

	//itor = std::find_first_of(bomb_list.begin(), bomb_list.end(), isActive);
	// place at parent position.
	// tick for a few seconds.
	// explode.
}

void World::Update()
{
	while (!messages->IsEmpty())
	{
		EventMessage_t msg = messages->PopFront();
		ParseMessage(msg);
	}

	if (game_timer->Milliseconds() - update_delta > tick_rate)
	{
		std::for_each(entities.begin(), entities.end(), std::mem_fun(&BaseEntity::Update));
		std::for_each(bomb_list.begin(), bomb_list.end(), std::mem_fun(&BombEntity::Update));
	}

	// collision loop. can we sort these by x and y position?
	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = i+1; j < entities.size(); ++j)
		{
			//std::cout << "j : " << j << std::endl;
		}
	}
}

void World::Render(Visualisation* vis) const
{
	double delta = (game_timer->Milliseconds() / update_delta) / tick_rate;
	vis->BeginScene();
	current_level->Render(vis);
	
	// draw active bombs
	for (const_bomb_itor it=bomb_list.begin(); it != bomb_list.end(); ++it)
	{
		if ((*it)->GetActive())
		{
			(*it)->Render(delta, vis);
		}
	}
	
	// draw active players
	for (const_ent_itor it=entities.begin(); it != entities.end(); ++it)
	{
		if ((*it)->GetActive())
		{
			(*it)->Render(delta, vis);
		}
	}

	vis->EndScene();
}

bool World::ChangeLevel(const std::string& level_name)
{
	if (current_level != nullptr)
	{
		delete current_level;
		current_level = new Level;
		
		if (!current_level->LoadData(level_name, 0, 1))
			return false;
		
		// all successful.
		return true;
	}
	else
		return false;
}

math::Vector2& World::FindFirstSpawn() const
{
	std::vector<SpawnPoint_t*>::const_iterator itor;
	itor = std::find_if(spawns.begin(), spawns.end(), boost::bind(&SpawnPoint_t::is_available,_1)==true);
	(*itor)->is_available = false;
	return (*itor)->position;
}

void World::AddPlayer(const int id)
{
	EntityImpl_t temp;
	temp.graphic_id = id;
	temp.direction = LEFT;
	temp.animation_frame = 7;
	temp.position = FindFirstSpawn();
	temp.previous_position = temp.position;
	temp.active = true;
	temp.level_copy = current_level;

	PlayerEntity *p = new PlayerEntity(temp);
	entities.push_back(p);
}

void World::FreeSpawnPoint(const math::Vector2& position)
{
	std::vector<SpawnPoint_t*>::const_iterator itor;
	itor = std::find_if(spawns.begin(), spawns.end(), boost::bind(&SpawnPoint_t::ComparePosition,_1, position) == true);
	(*itor)->is_available = true;
}

void World::CreateBombList(const int id)
{
	for (int i = 0; i < MAX_BOMBS; ++i)
	{
		BombEntity *b = new BombEntity;
		b->SetActive(false);
		b->SetSide(NONE);
		b->SetGraphicID(id);
		bomb_list.push_back(b);
	}
}

void World::ResetBomb(const int id)
{
	bomb_list[id]->SetActive(false);
	bomb_list[id]->SetSide(NONE);
	bomb_list[id]->SetPosition(math::Vector2(0,0));
}

void World::CreateExplosionList(const int id)
{
	for (int i = 0; i<NUM_EXPLOSIONS; ++i)
	{
		Explosion *e = new Explosion;
		explosion_list.push_back(e);
	}
}

void World::ParseMessage(const EventMessage_t& msg)
{
	switch (msg.event_type)
	{
	case EventMessage_t::DROP_BOMB:
		Action(msg.id);
		break;
	case EventMessage_t::FORWARD:
		entities[msg.id]->Move(math::Vector2(0, -4));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::BACK:
		entities[msg.id]->Move(math::Vector2(0, 4));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::LEFT:
		entities[msg.id]->Move(math::Vector2(-4, 0));
		entities[msg.id]->DoAnimation();
		break;
	case EventMessage_t::RIGHT:
		entities[msg.id]->Move(math::Vector2(4, 0));
		entities[msg.id]->DoAnimation();
		break;
	}
}