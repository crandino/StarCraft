#ifndef __MAP_H__
#define __MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "DList.h"
#include "Point2D.h"
#include "Module.h"

// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		p2SString name;
		int value;
	};

	~Properties()
	{
		doubleNode<Property*>* item;
		item = list.getFirst();

		while(item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.clear();
	}

	int get(const char* name, int default_value = 0) const;
	bool setPropertyValue(const char* name, int default_value);
	bool getPropertyValue(const char* name, int default_value);


	DList<Property*>	list;
};

// ----------------------------------------------------
struct MapLayer
{
	p2SString	name;
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

	p2SString			name;
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
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	DList<TileSet*>	tilesets;
	DList<MapLayer*>	layers;
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

	// Called each loop iteration
	void draw();

	// Called before quitting
	bool cleanUp();

	// Load new map
	bool load(const char* path);

	iPoint mapToWorld(int x, int y) const;
	iPoint worldToMap(int x, int y) const;
	bool createWalkabilityMap(int& width, int& height, uchar** buffer) const;
	bool setLayerProperty( char* name_layer, const char* name_property, int value);

private:

	bool loadMap();
	bool loadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool loadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool loadLayer(pugi::xml_node& node, MapLayer* layer);
	bool loadProperties(pugi::xml_node& node, Properties& properties);

	TileSet* getTilesetFromTileId(int id) const;

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __MAP_H__