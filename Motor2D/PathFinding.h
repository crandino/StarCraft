#ifndef __PATHFINDING_H__
#define __PATHFINDING_H_

#include "Module.h"
#include <vector>

struct pathList;

struct pathNode
{
	iPoint pos;  // Tile info
	int g, h;    // Score, cost
	const pathNode *parent;

	pathNode();
	pathNode(int score_g, int score_h, iPoint pos, const pathNode *parent_node);
	pathNode(const pathNode& node);

	// FindWalkableAdjacents: Fills a list of adjacent tiles that are walkable
	uint findAdjacents(pathList& list_to_fill) const;

	// FindWalkableAdjacents: Fills a list of adjacent tiles that are walkable
	uint findWalkableAdjacents(pathList& list_to_fill) const;
	
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

class PathFinding : public Module
{

private:

	vector<iPoint>    path_found;
	uchar*			    map_data;
	uint	       width, height;

public:

	PathFinding();
	~PathFinding();

	// Received all the info about the tiles and its walkability
	bool setMap(const uint &width, const uint &height, uchar *data);

	// CreatePath: Request to have a path from A to B
	int createPath(const iPoint& origin, const iPoint& destination);

	// GetLastPath: Returns order path step by step
	const vector<iPoint> &getLastPath() const;

	//Three utility methods :

	//CheckBoundaries: return true if pos is inside the map boundaries
	bool checkBoundaries(const iPoint& pos) const;

	// IsWalkable: returns true if the tile is walkable
	bool isWalkable(const iPoint& pos) const;

	//GetTileAt: return the walkability value of a tile
	uchar getTileAt(const iPoint& pos) const;

};

#endif // !__ PATHFINDING_H__
