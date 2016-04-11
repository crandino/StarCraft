#ifndef __MAP_H__
#define __MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "Point2D.h"
#include "Module.h"
#include "p2Defs.h"
#include <string>

enum WALKABILITY
{
	LOW_GROUND = 1,
	NO_WALKABLE = 2,
	HIGH_GROUND = 3
};

using namespace std;

// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		std::string name;
		int value;
	};

	~Properties()
	{
		list<Property*>::reverse_iterator item = listProperties.rbegin();

		while(item != listProperties.rend())
		{
			RELEASE(*item);
			item++;
		}

		listProperties.clear();
	}

	int get(const char* name, int default_value = 0) const;
	bool setPropertyValue(const char* name, int default_value);
	bool getPropertyValue(const char* name, int default_value);


	list<Property*>	listProperties;
};

// ----------------------------------------------------
struct MapLayer
{
	string	    name;
	int			width;
	int			height;
	uint*		data;
	Properties	properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect getTileRect(int id) const;

	string			    name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	string				name;
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	list<TileSet*>		tilesets;
	list<MapLayer*>		layers;

	TileSet* getTilesetFromTileId(int id) const;
};

// ----------------------------------------------------
class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	// Called before render is available
	bool awake(pugi::xml_node& conf);

	// Call before first frame
	bool start();

	// Called each loop iteration
	bool update(float dt);

	// Called each loop iteration
	void draw();

	// Called before quitting
	bool cleanUp();

	// Load new map
	bool load(const char* path);

	iPoint mapToWorld(MapData &map, int x, int y) const;
	iPoint worldToMap(MapData &map, int x, int y) const;
	bool createWalkabilityMap(int& width, int& height, uchar** buffer) const;
	bool setLayerProperty(const char* map_name, const char* layer_name, const char* property_name, int value);

	// CRZ 
	// Given an area, determine whether all this area is walkable.
	bool isAreaWalkable(const SDL_Rect &rect);
	void changeLogic(const SDL_Rect &rect, WALKABILITY walk_value);

private:

	bool loadMap(const char *map_name);
	bool loadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool loadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool loadLayer(pugi::xml_node& node, MapLayer* layer);
	bool loadProperties(pugi::xml_node& node, Properties& properties);

public:

	list<MapData> data;
	
private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded;
};

#endif // __MAP_H__