#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "Map.h"
#include "PathFinding.h"
#include "Scene.h"

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
	app->render->start_transition({ 880, 1974 });
   	int w, h;
	uchar *buffer = NULL;
	if(app->map->createWalkabilityMap(w, h, &buffer))
		app->path->setMap(w, h, buffer);

	// CRZ -> PathFinding testing
	/*path_tile = app->tex->loadTexture("temporaryTextures/path_tile.png");
	start_position.setZero();
	final_position.setZero();*/

	test = app->gui->createLabel("This is a sample text", 300, 300);
	rectangle_map_camera = app->gui->createImage(NULL, { 6, 229, 20, 13 });
	rectangle_map_camera->parent = rectangle_map;
	rectangle_map_camera->setLocalPos(3, 3);
	rectangle_map_camera->interactive = true;
	rectangle_map_camera->setListener(this);
	rectangle_map_camera->can_focus = true;
	rectangle_map_camera->draw_element = false;
	


	////ROF Start menu without interaction, it will be disabeled till it fully works
	//start_menu_img = app->tex->loadTexture("Screens/Start_Image.png");
	//start_menu = app->gui->createImage(start_menu_img, { 0, 0, 296, 336 });
	//start_menu->center();
	//start_menu->setLocalPos(start_menu->getLocalPos().x-5, start_menu->getLocalPos().y - 60);
	
	//Backgorund audio (DEBUG include)
	app->audio->playMusic("Audio/Music/Background_Music.mp3", 3.f);
	for (unsigned int i = 0; i <= 4; i++)
	{
		app->audio->volumeDown();
	}
	
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

	test->print("YOOO");
	// Debug ---
	//if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
	//{
	//	debug = !debug;
	//	if (debug)
	//		app->map->setLayerProperty("LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 0);
	//	else
	//		app->map->setLayerProperty("LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 1);
	//}

	/*if (app->input->getKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->loadGame("save_game.xml");

	if (app->input->getKey(SDL_SCANCODE_K) == KEY_DOWN)
		app->saveGame("save_game.xml");*/

	if (app->input->getKey(SDL_SCANCODE_KP_PLUS) == KEY_UP)
		app->audio->volumeUp();

	if (app->input->getKey(SDL_SCANCODE_KP_MINUS) == KEY_UP)
		app->audio->volumeDown();

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_P) == KEY_REPEAT)
		app->map->setLayerProperty("PROTOTYPE_LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 0);

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_O) == KEY_REPEAT)
		app->map->setLayerProperty("PROTOTYPE_LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 1);

	// Transition experiments
	/*if (app->input->getKey(SDL_SCANCODE_T) == KEY_DOWN)
		app->render->start_transition({ 2000, 2000 });*/
    
	// CRZ -> Code to test PathFinding! Do not delete! Some variables must be uncommented 
	// on the Header File
	/*if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (path_selected)
		{
			app->input->getMousePosition(final_position);
			final_position = app->render->screenToWorld(final_position.x, final_position.y);
			final_position = app->map->worldToMap(app->map->data.back(), final_position.x, final_position.y);
			app->path->createPath(start_position, final_position);
			path_selected = false;
		}
		else
		{
			app->input->getMousePosition(start_position);
			start_position = app->render->screenToWorld(start_position.x, start_position.y);
			start_position = app->map->worldToMap(app->map->data.back(), start_position.x, start_position.y);
			path_selected = true;
		}
	}

	iPoint start_pos = app->map->mapToWorld(app->map->data.back(), start_position.x, start_position.y);
	iPoint final_pos = app->map->mapToWorld(app->map->data.back(), final_position.x, final_position.y);
	app->render->blit(path_tile, start_pos.x, start_pos.y);
	app->render->blit(path_tile, final_pos.x, final_pos.y);
	vector<iPoint> path_found = app->path->getLastPath();
	for (vector<iPoint>::iterator it = path_found.begin(); it != path_found.end(); ++it)
	{
		iPoint pos; pos = app->map->mapToWorld(app->map->data.back(), it->x, it->y);
		app->render->blit(path_tile, pos.x, pos.y);
	}*/
	//--------------------------------------------------------------------------

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