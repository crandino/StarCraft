#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "Scene.h"
#include "Gui.h"

Scene::Scene() : Module()
{
	name.assign("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::awake(pugi::xml_node &node)
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::start()
{
	app->map->load("TEST_MAP.tmx");
    //app->map->load("LOGIC_MAP.tmx"); // This is the logic map where the units will be moving
	return true;
}

// Called each loop iteration
bool Scene::preUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::update(float dt)
{
	float cam_speed = 1.0f;

	/*if (app->input->getKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->loadGame("save_game.xml");

	if (app->input->getKey(SDL_SCANCODE_K) == KEY_DOWN)
		app->saveGame("save_game.xml");*/

	/* (app->input->getKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += cam_speed;

	if (app->input->getKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= cam_speed;

	if (app->input->getKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += cam_speed;

	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= cam_speed;*/

	if (app->input->getKey(SDL_SCANCODE_KP_PLUS) == KEY_UP)
		app->audio->volumeUp();

	if (app->input->getKey(SDL_SCANCODE_KP_MINUS) == KEY_UP)
		app->audio->volumeDown();

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_P) == KEY_REPEAT)
		app->map->setLayerProperty("Logic_Layer", "NoDraw", 0);

	if (app->input->getKey(SDL_SCANCODE_O) == KEY_REPEAT)
		app->map->setLayerProperty("Logic_Layer", "NoDraw", 1);

	// Transition experiments
	if (app->input->getKey(SDL_SCANCODE_T) == KEY_DOWN)
		app->render->start_transition({ 2000, 2000 });

	app->map->draw();

	app->gui->mouse->updatePosition();
	app->gui->mouse->draw();
	return true;
}

// Called each loop iteration
bool Scene::postUpdate()
{
	bool ret = true;

	if(app->input->getKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::cleanUp()
{
	LOG("Freeing scene");
	return true;
}