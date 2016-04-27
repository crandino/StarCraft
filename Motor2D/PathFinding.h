#ifndef __PATHFINDING_H__
#define __PATHFINDING_H_

#include "Module.h"
#include "Timer.h"
#include <map>
#include <vector>

struct pathList;

struct pathNode
{
	iPoint			pos;  // Tile info
	int				g, h;    // Score, cost
	const pathNode	*parent;

	pathNode();
	pathNode(int score_g, int score_h, iPoint pos, const pathNode *parent_node);
	pathNode(const pathNode& node);

	// FindAdjacents: Fills a list of adjacent tiles
	uint findAdjacents(pathList& list_to_fill, bool diagonals = false) const;

	// FindWalkableAdjacents: Fills a list of adjacent tiles that are walkable
	uint findWalkableAdjacents(pathList& list_to_fill, bool diagonals = false) const;
	
	// Score: Basically returns g + h
	int score() const;
	
	// CalculateF : Recalculates F based on distance to destination
	// Estimation("Manhattan distance")
	int calculateF(const iPoint& destination);
};

struct pathList
{
	//It contains a linked list of PathNode(not PathNode*)
	list<pathNode> list_of_nodes;

	//Find: Returns the node item if a certain node is in this list already(or NULL)
	list<pathNode>::iterator find(const iPoint& point);

	//GetNodeLowestScore: Returns the Pathnode with lowest score in this list or NULL if empty
	list<pathNode>::iterator getNodeLowestScore();
};

struct pathToFind
{
	//entity id
	uint		id;
	iPoint		destination;
	pathList	open_list;
	pathList	close_list;

	pathToFind();
	pathToFind(uint id, iPoint &destination);
};

class PathFinding : public Module
{

private:

	vector<iPoint>				path_found;
	map<uint, vector<iPoint>*>	paths_found;
	uchar*						map_data;
	uint						width, height;
	list<pathToFind>			paths_to_find;
	Timer						time_to_search;

public:

	PathFinding();
	~PathFinding();

	// Received all the info about the tiles and its walkability
	bool setMap(const uint &width, const uint &height, uchar *data);

	// CreatePath: Request to have a path from A to B
	int createPath(const iPoint& origin, const iPoint& destination, uint id);
	int createPathNow(const iPoint& origin, const iPoint& destination);
	
	// Called each loop iteration (searth for paths)
	bool postUpdate();

	// CreatePath: Request to have a path from A to adjacent
	int createPathToAdjacent(const iPoint& origin, uint distance);

	// findNearestWalkableTile: Returns the position of the nearest walkable tile
	// Radius set the maximum distance from the origin to success.
	iPoint findNearestWalkableTile(const iPoint &origin, const iPoint &destination, uint radius = 0) const;

	// GetLastPath: Returns order path step by step
	const vector<iPoint> &getLastPath() const;

	//getPathFound: return and erase order path step by step from their id if the path is found
	bool getPathFound(uint id, vector<iPoint> &path);

	//Three utility methods :

	//CheckBoundaries: return true if pos is inside the map boundaries
	bool checkBoundaries(const iPoint& pos) const;

	// IsWalkable: returns true if the tile is walkable
	bool isWalkable(const iPoint& pos) const;

	//GetTileAt: return the walkability value of a tile
	uchar getTileAt(const iPoint& pos) const;

};

#endif // !__ PATHFINDING_H__
