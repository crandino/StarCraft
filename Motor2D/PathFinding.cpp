#include "App.h"
#include "Point2d.h"
#include "PathFinding.h"

// Two interesting links about PathFinding
// Introduction: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Detailed: http://www.redblobgames.com/pathfinding/a-star/introduction.html

#define INVALID_WALKABILTY_CODE 255

pathNode::pathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL) { }
pathNode::pathNode(int g_score, int h_score, iPoint position, const pathNode *parent_node) : g(g_score), h(h_score), pos(position), parent(parent_node) { }
pathNode::pathNode(const pathNode &node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)  { }

uint pathNode::findAdjacents(pathList& list_to_fill) const
{
	uint items_before = list_to_fill.list_of_nodes.size();
	iPoint new_pos;
	uint items_added = 0;

	// North
	new_pos.set(pos.x, pos.y - 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	//North-West
	new_pos.set(pos.x - 1, pos.y - 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	// West
	new_pos.set(pos.x - 1, pos.y);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	//South-West
	new_pos.set(pos.x - 1, pos.y + 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	// South
	new_pos.set(pos.x, pos.y + 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	//South-East
	new_pos.set(pos.x + 1, pos.y + 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	// East
	new_pos.set(pos.x + 1, pos.y);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	//North-East
	new_pos.set(pos.x + 1, pos.y - 1);
	items_added++;
	list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));

	return items_added - items_before;
}

uint pathNode::findWalkableAdjacents(pathList& list_to_fill) const
{
	uint items_before = list_to_fill.list_of_nodes.size();
	iPoint new_pos;
	uint items_added = 0;

	// North
	new_pos.set(pos.x, pos.y - 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	//North-West
	new_pos.set(pos.x - 1, pos.y - 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	// West
	new_pos.set(pos.x - 1, pos.y);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	//South-West
	new_pos.set(pos.x - 1, pos.y + 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	// South
	new_pos.set(pos.x, pos.y + 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	//South-East
	new_pos.set(pos.x + 1, pos.y + 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	// East
	new_pos.set(pos.x + 1, pos.y);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	//North-East
	new_pos.set(pos.x + 1, pos.y - 1);
	if (app->path->isWalkable(new_pos))
	{
		items_added++;
		list_to_fill.list_of_nodes.push_back(pathNode(-1, -1, new_pos, this));
	}

	return items_added - items_before;
}

int pathNode::score() const
{
	return g + h;
}

int pathNode::calculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.distanceNoSqrt(destination);
	return g + h;
}

list<pathNode>::iterator pathList::find(const iPoint& point)
{
	list<pathNode>::iterator it = list_of_nodes.begin();
	while (it != list_of_nodes.end())
	{
		if (it->pos == point)
			return it;
		++it;
	}

	return it;
}

list<pathNode>::iterator pathList::getNodeLowestScore()
{
	int score = 65355;
	list<pathNode>::iterator it = list_of_nodes.begin();
	list<pathNode>::iterator lowest_score = list_of_nodes.end();
	while (it != list_of_nodes.end())
	{
		if (it->score() < score)
		{
			lowest_score = it;
			score = it->score();
		}			
		++it;
	}

	return lowest_score;
}

PathFinding::PathFinding()
{
	name.assign("path_finding");
}

PathFinding::~PathFinding()
{ 
	RELEASE_ARRAY(map_data);
}

bool PathFinding::setMap(const uint &width, const uint &height, uchar *data)
{
	this->width = width;
	this->height = height;

	if (data != NULL)
	{
		RELEASE_ARRAY(map_data);
		map_data = new uchar[width * height];
		memcpy(map_data, data, width*height);
	}

	return true;
}

int PathFinding::createPath(const iPoint& origin, const iPoint& destination)
{
	// Origin are walkable?
	if (!isWalkable(origin))
		return -1;

	iPoint changed_destination = destination;
	// Destination are walkable?
	if (!isWalkable(destination))
	{
		pathList open_list, close_list;

		open_list.list_of_nodes.push_back(pathNode(0, 0, destination, NULL));
		while (open_list.list_of_nodes.size() > 0)
		{
			list<pathNode>::iterator pnode = open_list.getNodeLowestScore();
			close_list.list_of_nodes.push_back(*pnode);
			iPoint pos = pnode->pos;
			open_list.list_of_nodes.erase(pnode);
			pnode = close_list.find(pos);

			if (app->path->isWalkable(pnode->pos))
			{
				changed_destination = pnode->pos;
				break;
			}

			pathList candidate_nodes;
			int items_added = pnode->findAdjacents(candidate_nodes);

			if (items_added > 0)
			{
				list<pathNode>::iterator item = candidate_nodes.list_of_nodes.begin();
				while (item != candidate_nodes.list_of_nodes.end())
				{
					if (close_list.find(item->pos) != close_list.list_of_nodes.end())
					{
						++item;
						continue;
					}
					else if (open_list.find(item->pos) != open_list.list_of_nodes.end())
					{
						list<pathNode>::iterator to_compare = open_list.find(item->pos);
						if (item->calculateF(origin) < to_compare->score())
						{
							to_compare->parent = item->parent;
							to_compare->calculateF(origin);
						}
					}
					else
					{
						item->calculateF(origin);
						open_list.list_of_nodes.push_back(*item);
					}
					++item;
				}
			}
		}
	}

	path_found.clear();

	// Open and close list
	pathList open_list, close_list;

	open_list.list_of_nodes.push_back(pathNode(0, 0, origin, NULL));
	while (open_list.list_of_nodes.size() > 0)
	{
		list<pathNode>::iterator pnode = open_list.getNodeLowestScore();
		close_list.list_of_nodes.push_back(*pnode);
		iPoint pos = pnode->pos;
		open_list.list_of_nodes.erase(pnode);
		pnode = close_list.find(pos);

		if (pnode->pos == changed_destination)
		{
			close_list.list_of_nodes.push_back(*pnode);
			break;
		}

		pathList candidate_nodes;
		int items_added = pnode->findWalkableAdjacents(candidate_nodes);

		if (items_added > 0)
		{
			list<pathNode>::iterator item = candidate_nodes.list_of_nodes.begin();
			while (item != candidate_nodes.list_of_nodes.end())
			{
				if (close_list.find(item->pos) != close_list.list_of_nodes.end())
				{
					++item;
					continue;
				}
				else if (open_list.find(item->pos) != open_list.list_of_nodes.end())
				{
					list<pathNode>::iterator to_compare = open_list.find(item->pos);
					if (item->calculateF(changed_destination) < to_compare->score())
					{
						to_compare->parent = item->parent;
						to_compare->calculateF(changed_destination);
					}
				}
				else
				{
					item->calculateF(changed_destination);
					open_list.list_of_nodes.push_back(*item);
				}
				++item;
			}
		}
	}


	const pathNode *final_path = &close_list.list_of_nodes.back();
	vector<iPoint> tmp;
	while (final_path != NULL)
	{
		tmp.push_back(final_path->pos);
		final_path = final_path->parent;
	}

	for (vector<iPoint>::reverse_iterator rit = tmp.rbegin(); rit != tmp.rend(); ++rit)
		path_found.push_back(*rit);

	path_found.erase(path_found.begin()); //we don't need the tile which is stepping

	return path_found.size();
}

const vector<iPoint> &PathFinding::getLastPath() const
{
	return path_found;
}

bool PathFinding::checkBoundaries(const iPoint& pos) const
{
	if (pos.x >= 0 &&
		pos.x <= width &&
		pos.y >= 0 &&
		pos.y <= height)
		return true;
	return false;
}

bool PathFinding::isWalkable(const iPoint& pos) const
{
	if (checkBoundaries(pos) && map_data[pos.y * width + pos.x] != 2)
		return true;
	return false;
}

uchar PathFinding::getTileAt(const iPoint& pos) const
{
	if (checkBoundaries(pos))
		return map_data[pos.y * width + pos.x];
	return INVALID_WALKABILTY_CODE;
}