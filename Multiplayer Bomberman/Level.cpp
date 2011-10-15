#include "Level.h"
#include "Visualisation.h"
#include <boost/bind.hpp>
#include <boost/random.hpp>
#include <fstream>
#include <ctime>

#pragma warning(disable:4018) // signed/unsigned mismatch

const int NUM_SPAWN_POINTS = 4;

Level::Level()
{
	num_tiles_high = 15; 
	num_tiles_wide = 20;

	tile_width = 16;
	tile_height = 16;
	
	spawn_points.reserve(NUM_SPAWN_POINTS);
	srand(time(0));
}

Level::Level(int tw, int th, int ntw, int nth) : tile_width(tw), tile_height(th),
	num_tiles_wide(ntw), num_tiles_high(nth)
{
	spawn_points.reserve(NUM_SPAWN_POINTS);
	srand(time(0));
}

Level::Level( Level * copy )
{
	(*this).num_tiles_high = copy->num_tiles_high;
	(*this).num_tiles_wide = copy->num_tiles_wide;
	(*this).tile_height = copy->tile_height;
	(*this).tile_width  = copy->tile_width;

	spawn_points.reserve(NUM_SPAWN_POINTS);
	srand(time(0));
}

Level::~Level()
{
	if (!tiles.empty())
		tiles.clear();

	if (!spawn_points.empty())
	{
		for (int i = 0; i < spawn_points.size(); ++i)
			delete spawn_points[i];
		
		spawn_points.clear();
	}
}

void Level::Render(Visualisation * vis)
{
	for (tile_itor it=tiles.begin(); it != tiles.end(); ++it)
		//if (!(*it).is_walkable)
		if((*it).tile_state & BRICK) 
			vis->DrawSprite((*it).id, math::Vector2(0,0), (*it).pos);
}

// check intersection between the two rectangles, player and tile.
bool Level::CheckTile( const math::Vector2& tile_position, rec::Rectangle& ent_rec )
{
	int tp = static_cast<int>(tile_position.x) / tile_width + 
		static_cast<int>(tile_position.y) / tile_height * num_tiles_wide;
	
	std::cout << "tp : " << tp << " pos : " << tiles[tp].pos << "\n";

	if (tp > tiles.size()-1 || tp < 0 || tile_position.x < 0 || tile_position.y < 0)
		return false;
	
	if (tiles[tp].is_walkable)
		return true;

	if (tiles[tp].tile_state & BRICK)
		return false;

	//return true;
	// Eats a brick!!!!
	//if (tiles[tp].tile_state &= ~BRICK)
	//	return true;
	
	//rec::Rectangle tile_rec = tiles[tp].collision_box;
	//rec::Rectangle entity_rec = ent_rec;

	/*tile_rec.left += tiles[tp].pos.x;
	tile_rec.right += tiles[tp].pos.x;
	tile_rec.top += tiles[tp].pos.y;
	tile_rec.bottom += tiles[tp].pos.y;*/

	/*entity_rec.left += tile_position.x;
	entity_rec.right += tile_position.x;
	entity_rec.top += tile_position.y;
	entity_rec.bottom += tile_position.y;*/

	//std::cout << "tile_rec = " << tile_rec.left << ": " << tile_rec.right << ": " << tile_rec.top << ": " << tile_rec.bottom << "\n";
	//std::cout << "entity_rec = " << entity_rec.left << ": " << entity_rec.right << ": " << entity_rec.top << ": " << entity_rec.bottom << "\n";
	
	/*return ((entity_rec.right < tile_rec.left || entity_rec.left > tile_rec.right) || 
		(entity_rec.bottom < tile_rec.top || entity_rec.top > tile_rec.bottom));*/
	
	//return ((tiles[tp].collision_box.right < entity_rec.left || tiles[tp].collision_box.left > entity_rec.right) || 
		//(tiles[tp].collision_box.bottom < entity_rec.top || tiles[tp].collision_box.top > entity_rec.bottom));
}

void Level::SurroundingTiles( std::vector<tile_t>& s, const math::Vector2& tile_position )
{
	std::vector<tile_t> tile_copy;
	
	int tp = static_cast<int>(tile_position.y / tile_height);
	tp = tp * num_tiles_wide;
	tp += static_cast<int>(tile_position.x / tile_width);

	if(tp > tiles.size()-1 || tp < 0 || !tiles[tp].is_walkable)
	{
		std::cerr << "invalid tile position " << tp << std::endl; 
		s = tile_copy;
		return;
	}

	for(int i = -1; i < 2; ++i)
	{
		int j = -1;
		int k = 2;
		
		//check to see if tile is on the left hand side
		if (tp % num_tiles_wide == 0)
			j = 0;
		
		//check to see if tile is on the right hand side 
		if (tp % num_tiles_wide == num_tiles_wide - 1)
			k = 1;
		
		for (j; j < k; ++j)
		{
			int adj = tp;
			adj = adj - (i * num_tiles_wide) + j;
			if (IsValidTile(adj, tp) && adj != tp)
			{
				tile_t tile = tiles[adj];
				tile_copy.push_back(tile);
			}
		}
	}

	s = tile_copy;
}

bool Level::IsValidTile( const int x, const int original ) const
{
	if (x < 0 || x > tiles.size()-1 || !tiles[x].is_walkable)
		return false;

	if (x > original + 1 && x < original + num_tiles_wide)
		if (!tiles[x + 1].is_walkable || !tiles[x - num_tiles_wide].is_walkable)
			return false;
	
	if (x > original && x > original + num_tiles_wide)
		if (!tiles[x - 1].is_walkable || !tiles[x - num_tiles_wide].is_walkable)
			return false;
	
	if (x < original && x < original - num_tiles_wide)
		if (!tiles[x + 1].is_walkable || !tiles[x + num_tiles_wide].is_walkable)
			return false;
	
	if (x < original - 1 && x > original-num_tiles_wide)
		if (!tiles[x - 1].is_walkable || !tiles[x + num_tiles_wide].is_walkable)
			return false;

	return true;
}

math::Vector2& Level::DestinationTile( const math::Vector2 destination )
{
	int pos = static_cast<int>(destination.y) / tile_height;
	pos = pos * num_tiles_wide + (static_cast<int>(destination.x) / tile_width);
	
	if (pos >= 0 && pos < tiles.size() && tiles[pos].is_walkable)
		return tiles[pos].pos;
	else 
		return tiles[pos].pos;
}

bool Level::LoadData( const std::string& filename, const int first_sprite, const int second_sprite ) 
{
	std::fstream level_data(filename.c_str());
	if (!level_data)
	{
		std::cout << "Error loading level data file." << std::endl;
		return false;
	}
	
	level_data >> tile_width >> tile_height >> num_tiles_wide >> num_tiles_high;
	for (int i = 0; i < num_tiles_high; ++i)
	{
		for (int j = 0; j < num_tiles_wide; ++j)
		{
			tile_t temp;
			temp.pos.x = j * tile_width;
			temp.pos.y = i * tile_height;
			
			temp.collision_box.left = temp.pos.x;
			temp.collision_box.right = temp.pos.x + tile_width;
			temp.collision_box.top = temp.pos.y;
			temp.collision_box.bottom = temp.pos.y + tile_height;

			int tile_number;
			level_data >> tile_number;
			
			switch(tile_number)
			{
			case 0: 
				temp.is_walkable = true;
				temp.id = -1;
				temp.tile_state = EMPTY;
				break;
			case 1: 
				temp.is_walkable = false;
				temp.id = first_sprite;
				temp.tile_state = BRICK | DESTROYABLE;
				break;
			case 2: 
				temp.is_walkable = false;
				temp.id = second_sprite;
				temp.tile_state = BRICK | NOT_DESTROYABLE;
				break;
			case 5:
				{
				temp.is_walkable = true;
				temp.id = -1;
				temp.tile_state = EMPTY;
				SpawnPoint_t *sp = new SpawnPoint_t(temp.pos);
				spawn_points.push_back(sp);
				break;
				}
			default: 
				break;
			}
			tiles.push_back(temp);
		}
	}

	level_data.close();

	if (tiles.empty())
		return false;

	return true;
}

bool Level::IsWalkable( const math::Vector2& position )
{
	for (std::vector<tile_t>::const_iterator it=tiles.begin(); it!=tiles.end(); ++it)
	{
		if ((*it).pos == position)
		{
			return (*it).is_walkable;
		}
	}
	return false;
}

math::Vector2 Level::GetRandomWalkableTile()
{
	math::Vector2 walkable;
	int index = rand() % tiles.size()-1;
	
	bool found = false;
	while (!found)
	{
		bool is_walkable = tiles[index].is_walkable;
		if (is_walkable)
		{
			walkable = tiles[index].pos;
			std::cout << "index is " << index << std::endl;
			break;
		}
		index = rand() % tiles.size()-1;
	}
	
	return walkable;
}

void Level::GetSpawnPoints( std::vector<SpawnPoint_t*>& sp )
{
	if (!spawn_points.empty())
		sp = spawn_points;
}

void Level::SetTileState( const math::Vector2& position, Uint32 new_states )
{
	tile_itor it = tiles.begin();
	it = std::find_if(tiles.begin(), tiles.end(), boost::bind(&tile_t::PositionPredicate, _1, position) == true);
	if (it != tiles.end())
		(*it).tile_state = new_states;
}

