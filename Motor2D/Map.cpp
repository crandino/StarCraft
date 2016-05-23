#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Render.h"
#include "FileSystem.h"
#include "Textures.h"
#include "PathFinding.h"
#include "Map.h"
#include <math.h>
#include <string>

Map::Map() : Module(), map_loaded(false)
{
	name.assign("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.assign(config.child("folder").child_value());
	return ret;
}

bool Map::start()
{
	app->map->load("FINAL_MAP.tmx");
	app->map->load("FINAL_MAP_LOGIC_16.tmx"); // This is the logic map where the units will be moving

	return true;
}

// Called each loop iteration
bool Map::update(float dt)
{
	draw();
	return true;
}

void Map::draw()
{
	if(map_loaded == false)
		return;
	
	// Maps to draw
	list<MapData>::iterator map_to_draw = data.begin();
	while (map_to_draw != data.end())
	{
		// For each map, we iterate each layer of this map
		list<MapLayer*>::iterator item = map_to_draw->layers.begin();
		for (; item != map_to_draw->layers.end(); item++)
		{
			MapLayer* layer = *item;
			if (layer->properties.get("NoDraw") != 0)
				continue;

			// Camera-culling: Render only blits what camera is showing. Behind Terran HUD it shouldn't blit.
			unsigned int hud_terran_height = 105;
			iPoint initial_tile = app->map->worldToMap(*map_to_draw , -app->render->camera.x, -app->render->camera.y);
			iPoint final_tile = app->map->worldToMap(*map_to_draw, -app->render->camera.x + app->render->camera.w, -app->render->camera.y + app->render->camera.h - hud_terran_height);

			iPoint blit_position = initial_tile;

			for (int y = initial_tile.y; y <= final_tile.y; ++y)
			{
				blit_position.x = initial_tile.x;
				for (int x = initial_tile.x; x <= final_tile.x; ++x)
				{
					int tile_id = layer->get(x, y);
					if (tile_id > 0)
					{
						TileSet* tileset = map_to_draw->getTilesetFromTileId(tile_id);   // Tileset for this tile_id
						SDL_Rect r = tileset->getTileRect(tile_id);		// Section of the tile within the tileset

						fPoint pos = mapToWorld(*map_to_draw, blit_position.x, blit_position.y);
						app->render->blit(tileset->texture, pos.x, pos.y, &r);
					}
					blit_position.x++;
				}
				blit_position.y++;
			}
		}
		++map_to_draw;
	}
}

bool Map::setLayerProperty(const char* map_name, const char* layer_name, const char* property_name, int value)
{
	list<MapData>::iterator map = data.begin();
	while (map != data.end())
	{
		if (map->name == map_name)
		{
			list<MapLayer*>::iterator layer = map->layers.begin();
			while (layer != map->layers.end())
			{
				if ((*layer)->name == layer_name)
				{
					(*layer)->properties.setPropertyValue(property_name, value);
					return true;
				}
				++layer;
			}
		}
		++map;
	}

	return false;
}

fPoint Map::mapToWorld(MapData &map, int x, int y) const
{
	fPoint ret;

	if (map.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * map.tile_width;
		ret.y = y * map.tile_height;
	}
	else if (map.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (map.tile_width * 0.5f);
		ret.y = (x + y) * (map.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint Map::worldToMap(MapData &map, int x, int y) const
{
	iPoint ret(0, 0);

	if (map.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / map.tile_width;
		if (ret.x < 0)
			ret.x = 0;
		else if (ret.x > map.width - 1)
			ret.x = map.width - 1;

		ret.y = y / map.tile_height;
		if (ret.y < 0)
			ret.y = 0;
		else if (ret.y > map.height - 1)
			ret.y = map.height - 1;
	}
	else if (map.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = map.tile_width * 0.5f;
		float half_height = map.tile_height * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2) - 1;
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

bool Map::isAreaWalkable(const SDL_Rect &rect, bool check_boundaries)
{
	iPoint first_tile = worldToMap(data.back(), rect.x, rect.y);
	iPoint last_tile = worldToMap(data.back(), rect.x + rect.w, rect.y + rect.h);
	iPoint point_to_check;
	if (check_boundaries)
	{
		first_tile -= (iPoint{ 1, 1 });
		last_tile += (iPoint{ 1, 1 });
	}

	for (int y = first_tile.y; y < last_tile.y; ++y)
	{
		for (int x = first_tile.x; x < last_tile.x; ++x)
		{
			point_to_check.set(x, y);
			if (!app->path->isWalkable({ x, y }))
				return false;
		}
	}

	return true;
}

bool Map::changeLogic(const SDL_Rect &rect, WALKABILITY walk_value)
{
	// Right now, there is only one logic map and only one logic layer, so we must not iterate them.
	list<MapLayer*>::iterator layer = app->map->data.back().layers.begin();
	while (layer != app->map->data.back().layers.end())
	{
		iPoint first_tile = app->map->worldToMap(app->map->data.back(), rect.x, rect.y);
		iPoint last_tile = app->map->worldToMap(app->map->data.back(), rect.x + rect.w, rect.y + rect.h);

		for (int y = first_tile.y; y < last_tile.y; ++y)
		{
			for (int x = first_tile.x; x < last_tile.x; ++x)
			{
				(*layer)->data[y * (*layer)->width + x] = walk_value;
			}
		}
	++layer;
	}

	// We update the walkability map
	int w, h;
	uchar *buffer = NULL;
	if (app->map->createWalkabilityMap(w, h, &buffer))
		app->path->setMap(w, h, buffer);

	return true;
}

int Properties::get(const char* value, int default_value) const
{
	list<Property*>::const_iterator item = listProperties.begin();
	
	while(item != listProperties.end())
	{
		if((*item)->name == value)
			return (*item)->value;
		item++;
	}

	return default_value;
}

bool Properties::setPropertyValue(const char* name, int default_value)
{
	list<Property*>::iterator item = listProperties.begin();

	for (item; item != listProperties.end(); item++)
	{
		if ((*item)->name == name)
		{
			(*item)->value = default_value;
			return true;
		}
	}

	return false;
}

TileSet* MapData::getTilesetFromTileId(int id) const
{
	// Pick the right Tileset based on a tile id
	list<TileSet*>::const_iterator set_item = tilesets.begin();
	TileSet *tileset = *set_item;

	while (set_item != tilesets.end())
	{
		if (id >= (*set_item)->firstgid)
			tileset = (*set_item);
		++set_item;
	}

	return tileset;
}

SDL_Rect TileSet::getTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool Map::cleanUp()
{
	LOG("Unloading map");

	list<MapData>::iterator item_map = data.begin();
	while (item_map != data.end())
	{
		// Remove all tilesets
		list<TileSet*>::iterator item = item_map->tilesets.begin();

		while (item != item_map->tilesets.end())
		{
			RELEASE(*item);
			item++;
		}
		item_map->tilesets.clear();

		// Remove all layers
		list<MapLayer*>::iterator item2 = item_map->layers.begin();

		while (item2 != item_map->layers.end())
		{
			RELEASE(*item2);
			item2++;
		}
		item_map->layers.clear();
		
		++item_map;
	}	

	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool Map::load(const char* file_name)
{
	bool ret = true;
	char c[512];
	sprintf_s(c, "%s%s", folder.data(), file_name);
	string tmp; tmp.assign(c);

	char* buf;
	int size = app->fs->load(tmp.data(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = loadMap(file_name);
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = loadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = loadTilesetImage(tileset, set);
		}

		data.back().tilesets.push_back(set);
	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for(layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = loadLayer(layer, lay);

		if(ret == true)
			data.back().layers.push_back(lay);
	}

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.back().width, data.back().height);
		LOG("tile_width: %d tile_height: %d", data.back().tile_width, data.back().tile_height);

		list<TileSet*>::iterator item = data.back().tilesets.begin();
		
		while (item != data.back().tilesets.end())
		{
			TileSet* s = (*item);
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.data(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item++;
		}

		list<MapLayer*>::iterator item_layer = data.back().layers.begin();
		while (item_layer != data.back().layers.end())
		{
			MapLayer* l = (*item_layer);
			LOG("Layer ----");
			LOG("name: %s", l->name.data());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer++;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool Map::loadMap(const char *map_name)
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		MapData map_info;
		map_info.name = map_name;
		map_info.width = map.attribute("width").as_int();
		map_info.height = map.attribute("height").as_int();
		map_info.tile_width = map.attribute("tilewidth").as_int();
		map_info.tile_height = map.attribute("tileheight").as_int();
		string bg_color(map.attribute("backgroundcolor").as_string());

		map_info.background_color.r = 0;
		map_info.background_color.g = 0;
		map_info.background_color.b = 0;
		map_info.background_color.a = 0;

		if(bg_color.length() > 0)
		{
			string red, green, blue;
			red = bg_color.substr(1, 2);
			green = bg_color.substr(3, 4);
			blue = bg_color.substr(5, 6);
			
			int v = 0;

			sscanf_s(red.data(), "%x", &v);
			if (v >= 0 && v <= 255) map_info.background_color.r = v;

			sscanf_s(green.data(), "%x", &v);
			if (v >= 0 && v <= 255) map_info.background_color.g = v;

			sscanf_s(blue.data(), "%x", &v);
			if (v >= 0 && v <= 255) map_info.background_color.b = v;
		}

		string orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			map_info.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			map_info.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			map_info.type = MAPTYPE_STAGGERED;
		}
		else
		{
			map_info.type = MAPTYPE_UNKNOWN;
		}

		data.push_back(map_info);
	}

	return ret;
}

bool Map::loadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.assign(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool Map::loadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = app->tex->loadTexture(PATH(folder.data(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool Map::loadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	loadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if(layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for(pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::loadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if(data != NULL)
	{
		pugi::xml_node prop;

		for(prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.listProperties.push_back(p);
		}
	}

	return ret;
}

bool Map::createWalkabilityMap(int& width, int& height, uchar** buffer) const
{
	bool ret = false;
	const MapData *logic_map = &(data.back());
	
	list<MapLayer*>::const_iterator layers = logic_map->layers.begin();

	for (layers; layers != logic_map->layers.end(); ++layers)
	{
		MapLayer *layer = *layers;

		if(layer->properties.get("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width*layer->height];
		memset(map, 1, layer->width*layer->height);

		for (int y = 0; y < logic_map->height; ++y)
		{
			for (int x = 0; x < logic_map->width; ++x)
			{
				int i = (y*layer->width) + x;

				int tile_id = layer->get(x, y);
				TileSet* tileset = (tile_id > 0) ? logic_map->getTilesetFromTileId(tile_id) : NULL;
				
				if(tileset != NULL)
				{
					// This code only works for our Tile ID configuration present on Path_tiles.png
					//map[i] = (tile_id - tileset->firstgid) > 0 ? 0 : 1;
					map[i] = tile_id;
				}
			}
		}

		*buffer = map;
		width = logic_map->width;
		height = logic_map->height;
		ret = true;

		break;
	}

	return ret;
}