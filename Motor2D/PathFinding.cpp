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

	// West
	new_pos.set(pos.x - 1, pos.y);
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

	// East
	new_pos.set(pos.x + 1, pos.y);
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
	h = abs(destination.x - pos.x) + abs(destination.y - pos.y); // pos.distanceTo(destination);
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
			lowest_score = it;
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
	// Origin and destination are walkable?
	if (!isWalkable(origin) || !isWalkable(destination))
		return -1;

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

		if (pnode->pos == destination)
		{
			close_list.list_of_nodes.push_back(*pnode);
			break;
		}

		pathList candidate_nodes;		
		int items_added = pnode->findWalkableAdjacents(candidate_nodes);

		if (items_added > 0)
		{
			list<pathNode>::iterator item = candidate_nodes.list_of_nodes.end();
			--item;
			while (item != candidate_nodes.list_of_nodes.begin())
			{
				if (close_list.find(item->pos) != close_list.list_of_nodes.end())
				{
					--item;
					continue;
				}
				else if (open_list.find(item->pos) != open_list.list_of_nodes.end())
				{
					list<pathNode>::iterator to_compare = open_list.find(item->pos);
					if (item->calculateF(destination) < to_compare->score())
					{
						to_compare->parent = item->parent;
						to_compare->calculateF(destination);
					}
				}
				else
				{
					item->calculateF(destination);
					open_list.list_of_nodes.push_back(*item);
				}
				--item;
			}
		}
	}


	const pathNode *item = &close_list.list_of_nodes.back();
	vector<iPoint> tmp;
	while (item != NULL)
	{
		tmp.push_back(item->pos);
		item = item->parent;
	}
	
	// Reversing path, from origin to destination
	for (uint i = tmp.size() - 1; i >= 0; --i)
		path_found.push_back(tmp[i]);

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
	if (checkBoundaries(pos) && map_data[pos.y * width + pos.x] != 0)
		return true;
	return false;
}

uchar PathFinding::getTileAt(const iPoint& pos) const
{
	if (checkBoundaries(pos))
		return map_data[pos.y * width + pos.x];
	return INVALID_WALKABILTY_CODE;
}