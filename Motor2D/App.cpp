#include "p2Defs.h"
#include "p2Log.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "FileSystem.h"
#include "Map.h"
#include "App.h"

#include <iostream> 
#include <sstream> 

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	want_to_save = want_to_load = false;

	input = new Input();
	win = new Window();
	render = new Render();
	tex = new Textures();
	audio = new Audio();
	scene = new Scene();
	fs = new FileSystem();
	map = new Map();

	// Ordered for awake / start / update
	// Reverse order of cleanUp
	addModule(fs);
	addModule(input);
	addModule(win);
	addModule(tex);
	addModule(audio);
	addModule(map);
	
	addModule(scene);

	// render last to swap buffer
	addModule(render);
}

// Destructor
App::~App()
{
	// release modules
	doubleNode<Module*>* item = modules.getLast();

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->previous;
	}

	modules.clear();
	config_file.reset();
}

void App::addModule(Module* module)
{
	module->init();
	modules.add(module);
}

pugi::xml_node App::loadConfig(pugi::xml_document& config_file) const
{
	// --- load config file ---
	char* buf;
	int size = app->fs->load("config.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	}

	return config_file.child("config");
}

// Called before render is available
bool App::awake()
{
	bool ret = true;

	pugi::xml_document config_file;
	pugi::xml_node config_node;

	config_node = loadConfig(config_file);

	frame_rate = config_node.child("app").attribute("framerate").as_int(0);

	doubleNode<Module*>* item = modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->awake(config_node.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

// Called before the first frame
bool App::start()
{
	avg_fps = 0.0f;
	seconds_since_startup = 0.0f;
	last_frame_ms = 0;
	frames_on_last_update = 0;
	frame_count = 0;

	last_time = 0.0f;
	last_frames = 0;

	total_time.start();

	bool ret = true;
	doubleNode<Module*>* item;
	item = modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->start();
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::update()
{
	bool ret = true;
	prepareUpdate();

	if(input->getWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = preUpdate();

	if(ret == true)
		ret = doUpdate();

	if(ret == true)
		ret = postUpdate();

	finishUpdate();
	return ret;
}

// ---------------------------------------------
void App::prepareUpdate()
{
	// Starting timers
	timer.start();

	// Calculate dt. Differential time since last frame.
	dt = dt_timer.read();
	dt_timer.start();
}

// ---------------------------------------------
void App::finishUpdate()
{
	if (want_to_load == true) loadGameNow();
	if (want_to_save == true) saveGameNow();

	// Amount of frames since startup
	frame_count++;
	// Amount of time since game start (use a low resolution timer)
	seconds_since_startup = total_time.readSec();
	// Average FPS for the whole game life
	avg_fps = frame_count / seconds_since_startup;
	// Amount of ms took the last update
	last_frame_ms = timer.read();
	// Amount of frames during the last second
	if (seconds_since_startup - last_time > 1.0f)
	{
		frames_on_last_update = (frame_count - last_frames) / (seconds_since_startup - last_time);
		last_time = seconds_since_startup;
		last_frames = frame_count;
	}

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last sec frames: %u Last dt: %u Time since startup: %.3f Frame Count: %lu ",
		avg_fps, frames_on_last_update, last_frame_ms, seconds_since_startup, frame_count);

	app->win->setTitle(title);

	// Delay to achieve cap framerate
	if (frame_rate != 0)
	{
		if (((1000.0f / frame_rate) - last_frame_ms) > 0)
		{
			Uint32 delay = (1000.0f / frame_rate) - last_frame_ms;
			perf_timer.start();
			SDL_Delay(delay);
			LOG("Time to delay: %d , Time delayed %f", delay, perf_timer.readMs());
		}						
	}	
}

// Call modules before each loop iteration
bool App::preUpdate()
{
	bool ret = true;
	doubleNode<Module*>* item;
	item = modules.getFirst();
	Module* pModule = NULL;

	for(item = modules.getFirst(); item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->preUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::doUpdate()
{
	bool ret = true;
	doubleNode<Module*>* item;
	item = modules.getFirst();
	Module* pModule = NULL;

	for(item = modules.getFirst(); item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::postUpdate()
{
	bool ret = true;
	doubleNode<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.getFirst(); item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->postUpdate();
	}

	return ret;
}

// Called before quitting
bool App::cleanUp()
{
	bool ret = true;
	doubleNode<Module*>* item;
	item = modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->cleanUp();
		item = item->previous;
	}

	return ret;
}

// ---------------------------------------
int App::gerArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::gerArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// Load/Save
void App::loadGame(const char *file)
{
	want_to_load = true;
	load_game.create("%s%s", fs->getSaveDirectory(), file);
	
}

void App::saveGame(const char *file) const
{
	want_to_save = true;
	//save_game.create("%s%s", fs->getSaveDirectory(), file);
	save_game.create(file);
}

bool App::loadGameNow()
{
	bool ret = true;

	char *buffer;
	uint size = fs->load(load_game.GetString(), &buffer);

	if (size > 0)
	{
		// We create the necessary elements from pugiXML
		pugi::xml_document	data;
		pugi::xml_node		root;

		pugi::xml_parse_result result = data.load_buffer(buffer, size);
		RELEASE(buffer);

		if (result != NULL)
		{
			LOG("Loading new Game State from %s...", load_game.GetString());
			root = data.child("game_state");

			doubleNode<Module*> *item = modules.getFirst();
			for (; item != NULL && ret != false; item = item->next)
			{
				ret = item->data->load(root.child(item->data->name.GetString()));
			}

			data.reset();
			if (ret == true)
				LOG("...finished loading");
			else
				LOG("...loading process interrupted with error on module %s", (item != NULL) ? item->data->name.GetString() : "unknown");
		}
		else
			LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());
	}
	else
		LOG("Could not load game state xml file %s", load_game.GetString());

	want_to_load = false;
	return ret;
}

bool App::saveGameNow() const
{
	bool ret = true;

	LOG("Saving Game State on %s...", save_game.GetString());

	// Necesary elements from PugiXML
	pugi::xml_document data;
	pugi::xml_node	   root;

	root = data.append_child("game_state");

	doubleNode<Module*> *item = modules.getFirst();
	for (; item != NULL && ret != false; item = item->next)
	{
		ret = item->data->save(root.append_child(item->data->name.GetString()));
	}

	if (ret != false)
	{
		std::stringstream stream;
		data.save(stream);

		fs->save(save_game.GetString(), stream.str().c_str(), stream.str().length());
		LOG("... finishing saving %s.", save_game.GetString());
	}
	else
		LOG("Save process halted from an error in module %s", (item != NULL) ? item->data->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}

uint App::getFrameRate() const
{
	return frames_on_last_update != 0 ? frames_on_last_update : 30;
}