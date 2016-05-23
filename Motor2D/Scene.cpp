#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "Map.h"
#include "GameManager.h"
#include "PathFinding.h"
#include "Scene.h"
#include "FogOfWar.h"

#include "GuiImage.h"
#include "GuiLabel.h"

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
	// Scene loading...

	// ---- GAME MANAGER ----
	app->game_manager->initiateGame();
	
	// ---- MAPS ----
	app->map->data.front().layers.front()->properties.setPropertyValue("NoDraw", 0);	

	// ---- PATHFINDING ---
	int w, h;
	uchar *buffer = NULL;
	if (app->map->createWalkabilityMap(w, h, &buffer))
		app->path->setMap(w, h, buffer);

	// ---- FOG OF WAR ----
	app->fog_of_war->setUp(app->map->data.front().tile_width * app->map->data.front().width,
						   app->map->data.front().tile_height * app->map->data.front().height, 32, 32, 1);
	fog_of_war_timer.start();

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

	if (app->input->getKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->loadGame("save_game.xml");

	if (app->input->getKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->saveGame("save_game.xml");

	if (app->input->getKey(SDL_SCANCODE_KP_PLUS) == KEY_UP)
		app->audio->volumeUp();

	if (app->input->getKey(SDL_SCANCODE_KP_MINUS) == KEY_UP)
		app->audio->volumeDown();

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_P) == KEY_REPEAT)
		app->map->setLayerProperty("FINAL_MAP_LOGIC_16.tmx", "Logic_Layer", "NoDraw", 0);

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_O) == KEY_REPEAT)
		app->map->setLayerProperty("FINAL_MAP_LOGIC_16.tmx", "Logic_Layer", "NoDraw", 1);

	//--------------------------------------------------------------------------
	//FOG_OF_WAR 3 - Scene update.Called once every frame.
	//Draw the Fog of War
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	//FOG_OF_WAR
	if (!debug)
	{
		app->entity_manager->updateFogOfWar();
		app->fog_of_war->draw();
	}
	else
		app->fog_of_war->maps.back()->setAll(true);

	return true;
}

// Called each loop iteration
bool Scene::postUpdate()
{
	//FOG_OF_WAR 5 - Scene PosUpdate. Called once every frame.
	//Clear the low alpha map
	if (!debug && (uint)fog_of_war_timer.read() > 500) // Every 0.5 seconds, the fog of war is reset to maxAlpha value (175);
	{
		fog_of_war_timer.start();
		app->fog_of_war->clearMap(0);
		app->entity_manager->updateFogOfWar();
	}

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

//GUI
void Scene::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == rectangle_map)
	{
		if (event == GUI_EVENTS::MOUSE_LCLICK_DOWN)
		{
			iPoint pos_rect;
			app->input->getMousePosition(pos_rect);
			SDL_Rect rect_map_camera_parent = rectangle_map_camera->parent->getScreenRect();
			if (pos_rect.x + rectangle_map_camera->getScreenRect().w <= rect_map_camera_parent.x + rect_map_camera_parent.w
				&& pos_rect.y + rectangle_map_camera->getScreenRect().h < rect_map_camera_parent.y + rect_map_camera_parent.h)
				rectangle_map_camera->setLocalPos(pos_rect.x - rectangle_map_camera->parent->getLocalPos().x, pos_rect.y - rectangle_map_camera->parent->getLocalPos().y);

			else if (pos_rect.x + rectangle_map_camera->getScreenRect().w > rect_map_camera_parent.x + rect_map_camera_parent.w && pos_rect.x < rect_map_camera_parent.x + rect_map_camera_parent.w)
			{
				int i = (pos_rect.x + rectangle_map_camera->getScreenRect().w) - (rect_map_camera_parent.x + rect_map_camera_parent.w);
				rectangle_map_camera->setLocalPos(pos_rect.x - rectangle_map_camera->parent->getLocalPos().x - i, pos_rect.y - rectangle_map_camera->parent->getLocalPos().y);
			}
			else if (pos_rect.y + rectangle_map_camera->getScreenRect().h > rect_map_camera_parent.y + rect_map_camera_parent.h && pos_rect.y < rect_map_camera_parent.y + rect_map_camera_parent.h)
			{
				int i = (pos_rect.y + rectangle_map_camera->getScreenRect().h) - (rect_map_camera_parent.y + rect_map_camera_parent.h);
				rectangle_map_camera->setLocalPos(pos_rect.x - rectangle_map_camera->parent->getLocalPos().x, pos_rect.y - rectangle_map_camera->parent->getLocalPos().y - i);
			}

			else if (pos_rect.x + rectangle_map_camera->getScreenRect().w > rect_map_camera_parent.x + rect_map_camera_parent.w && pos_rect.x < rect_map_camera_parent.x + rect_map_camera_parent.w
				&& pos_rect.y + rectangle_map_camera->getScreenRect().h > rect_map_camera_parent.y + rect_map_camera_parent.h && pos_rect.y < rect_map_camera_parent.y + rect_map_camera_parent.h)
			{
				int i = (pos_rect.x + rectangle_map_camera->getScreenRect().w) - (rect_map_camera_parent.x + rect_map_camera_parent.w);
				int i2 = (pos_rect.y + rectangle_map_camera->getScreenRect().h) - (rect_map_camera_parent.y + rect_map_camera_parent.h);
				rectangle_map_camera->setLocalPos(pos_rect.x - rectangle_map_camera->parent->getLocalPos().x - i, pos_rect.y - rectangle_map_camera->parent->getLocalPos().y - i2);
			}

		}
	}
	
}