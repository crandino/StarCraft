#include "App.h"
#include "FileSystem.h"
#include "LevelManager.h"
#include "p2Log.h"

LevelManager::LevelManager() : Module()
{
	name.create("level_manager");
}

// Destructor
LevelManager::~LevelManager()
{}

bool LevelManager::awake(pugi::xml_node &node)
{
	num_of_levels = node.child("general_conf").attribute("num_of_levels").as_int();
	load_level(2);
	return true;
}

bool LevelManager::preUpdate()
{
	return true;
}

bool LevelManager::update(float dt)
{
	return true;
}

bool LevelManager::postUpdate()
{
	return true;
}

bool LevelManager::cleanUp()
{
	return true;
}

const LevelData *LevelManager::load_level(uint number_level)
{
	if (number_level > 0 && number_level <= num_of_levels)
	{
		pugi::xml_document doc;
		pugi::xml_node	   level_info;

		char* buf;
		int size = app->fs->load("config.xml", &buf);
		pugi::xml_parse_result result = doc.load_buffer(buf, size);
		RELEASE(buf);

		if (result == NULL)
			LOG("Could not load level info from xml file config.xml. pugi error: %s", result.description());

		char level[128];
		sprintf_s(level, "%s%d", "level", number_level);
		level_info = doc.child("config").child("level_manager").child("levels_data").child(level);

		LevelData *l = new LevelData();
		l->fire_ratio = level_info.attribute("fire_ratio").as_int();
		l->ice_ratio = level_info.attribute("ice_ratio").as_int();
		l->grass_ratio = level_info.attribute("grass_ratio").as_int();
		return l;
	}
	else
	{
		LOG("There are only %d available levels, starting at 1. Unable to load level number %d", num_of_levels, number_level);
		return NULL;
	}
}