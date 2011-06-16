#include "AStar.h"
#include "Timer.h"
#include "Level.h"

#include <iostream>
#include <algorithm>
#include <string>

bool compareFValues( const node_t& n1, const node_t& n2 )
{
	return ((n1.g_score + n1.h_score) < (n2.g_score + n2.h_score));
}

AStar::AStar() : level_copy(NULL)
{
}

AStar::AStar( Level * l ) : level_copy(l)
{
}

AStar::~AStar()
{
}

void AStar::Search( std::vector<node_t>& path, const math::Vector2& position, const math::Vector2& goal )
{
	int ID = 1;
	
	node_t start_node;
	start_node.position = position;
	start_node.id = ID;
	start_node.parent_id = 0;
	start_node.g_score = 0;
	start_node.h_score = CalculateH(position, goal);

	++ID;
	open_list.push_back(start_node);
	
	bool found = false;
	while (!found)
	{
		std::sort(open_list.begin(), open_list.end(), compareFValues);
		
		if (open_list[0].position == goal)
		{
			closed_list.push_back(open_list[0]);
			open_list[0] = open_list.back();
			open_list.pop_back();
			found = true;
			break;
		}
		
		std::vector<tile_t> surrounding_tiles;
		level_copy->SurroundingTiles(surrounding_tiles, open_list[0].position);
		
		for (Level::tile_itor i = surrounding_tiles.begin();i!=surrounding_tiles.end();++i)
		{
			bool add_node = true;
			for (node_itor j = closed_list.begin();j!=closed_list.end();++j)
			{
				if (i->pos == j->position)
					add_node = false;
			}
		
			for (node_itor j = open_list.begin();j!=open_list.end();++j)
			{
				if (i->pos == j->position)
				{
					int g = CalculateG(i->pos,open_list[0].position, open_list[0].g_score);
					if (g < j->g_score)
					{
						j->g_score = g;
						j->parent_id = open_list[0].id;
						add_node = false;
					}
				}
			}
		
			if (add_node)
			{
				node_t valid_node;
				valid_node.id = ID;
				valid_node.parent_id = open_list[0].id;
				valid_node.position = (*i).pos;
				valid_node.g_score = CalculateG((*i).pos, open_list[0].position, open_list[0].g_score);
				valid_node.h_score = CalculateH((*i).pos, goal);				
				open_list.push_back(valid_node);
				++ID;
			}

		}
		
		closed_list.push_back(open_list[0]);
		open_list[0] = open_list.back();
		open_list.pop_back();
	}

	bool route = false;
	int current_node = closed_list.size() - 1;
	
	while (!route)
	{
		successors.push_back(closed_list[current_node]);
		if (closed_list[current_node].position == position)
			route = true;

		current_node = closed_list[current_node].parent_id;
		closed_list.pop_back();
		
		for (size_t i = 0; i < closed_list.size(); ++i)
		{
			if (current_node == closed_list[i].id)
			{
				current_node = i;
				break;
			}
		}
	}
	
	path = successors;

	open_list.clear();
	closed_list.clear();
	successors.clear();
}

int AStar::CalculateG( const math::Vector2& pos, const math::Vector2& parent_pos, const int parent_g )
{
	int x = abs(pos.x - parent_pos.x);
	int y = abs(pos.y - parent_pos.y);

	math::Vector2 dim(level_copy->TileDimensions());
	x = x / dim.x;
	y = y / dim.y;
	x = x - y;

	if (x == 0)
		return 14 + parent_g;
	else if (x == 1 || x == -1)
		return 10 + parent_g;
	else
		return 0;
}

int AStar::CalculateH( const math::Vector2& pos, const math::Vector2 &dest )
{
	int x = abs(pos.x - dest.x);
	int y = abs(pos.y - dest.y);

	math::Vector2 dim(level_copy->TileDimensions());
	x = x / dim.x;
	y = y / dim.y;

	return (x + y) * 10;
}