#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "PathFinding.h"
#include "Scene.h"
#include "Gui.h"
#include "Animation.h"

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
    app->map->load("LOGIC_MAP.tmx"); // This is the logic map where the units will be moving

	int w, h;
	uchar *buffer = NULL;
	if(app->map->createWalkabilityMap(w, h, &buffer))
		app->path->setMap(w, h, buffer);

	mouse_texture = app->tex->loadTexture("StarCraftCursors.png");

	ui_terran = app->gui->createImage(NULL, { 0, 365, 800, 235 });
	ui_terran->setLocalPos(0, 365);
	ui_terran->interactive = true;
	ui_terran->setListener(this);
	ui_terran->can_focus = true;

	rectangle_map = app->gui->createImage(NULL, { 0, 0, 168, 164 });
	rectangle_map->setLocalPos(4, 433);
	rectangle_map->interactive = true;
	rectangle_map->setListener(this);
	rectangle_map->can_focus = true;

	rectangle_map_camera = app->gui->createImage(NULL, { 67, 298, 26, 18 });
	rectangle_map_camera->parent = rectangle_map;
	rectangle_map_camera->setLocalPos(3, 3);
	rectangle_map_camera->interactive = true;
	rectangle_map_camera->setListener(this);
	rectangle_map_camera->can_focus = true;

	
	//Cursor
	//IDLE
	cursor_animation_idle.frames.push_back({ 2, 2, 40, 42 });
	cursor_animation_idle.frames.push_back({ 46, 2, 40, 42 });
	cursor_animation_idle.frames.push_back({ 90, 2, 40, 42 });
	cursor_animation_idle.frames.push_back({ 134, 2, 40, 42 });
	cursor_animation_idle.frames.push_back({ 178, 2, 40, 42 });
	cursor_animation_idle.speed = 0.02f;
	cursor_animation_idle.loop = true; 
	
	//LEFT
	cursor_animation_left.frames.push_back({ 178, 232, 40, 42 });
	cursor_animation_left.frames.push_back({ 222, 232, 40, 42 });
	cursor_animation_left.speed = 0.02f;
	cursor_animation_left.loop = true;
	
	//RIGHT
	cursor_animation_right.frames.push_back({ 530, 232, 40, 42 });
	cursor_animation_right.frames.push_back({ 574, 232, 40, 42 });
	cursor_animation_right.speed = 0.02f;
	cursor_animation_right.loop = true;
	
	//UP
	cursor_animation_up.frames.push_back({ 354, 232, 40, 42 });
	cursor_animation_up.frames.push_back({ 398, 232, 40, 42 });
	cursor_animation_up.speed = 0.02f;
	cursor_animation_up.loop = true;
	
	//DOWN
	cursor_animation_down.frames.push_back({ 2, 232, 40, 42 });
	cursor_animation_down.frames.push_back({ 46, 232, 40, 42 });
	cursor_animation_down.speed = 0.02f;
	cursor_animation_down.loop = true;
	
	mouse = app->gui->createCursor(mouse_texture, &cursor_animation);
	mouse->setLocalPos(app->input->getMouseMotion().x, app->input->getMouseMotion().y);
    
	SDL_ShowCursor(SDL_DISABLE);
	
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
		app->map->setLayerProperty("LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 0);

	// Paint Layers -- Draw or undraw the map
	if (app->input->getKey(SDL_SCANCODE_O) == KEY_REPEAT)
		app->map->setLayerProperty("LOGIC_MAP.tmx", "Logic_Layer", "NoDraw", 1);

	// Transition experiments
	if (app->input->getKey(SDL_SCANCODE_T) == KEY_DOWN)
		app->render->start_transition({ 2000, 2000 });
    
	app->map->draw();
	mouse->updatePosition();

	//Provisional--------------------------------------------------------------
	//MouseQuad
	/*if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
	{
		if (quad_counter == 0)
			app->input->getMousePosition(init_mouse);
		
		selection = app->gui->mouseQuad(init_mouse);
		quad_counter++;
	}

	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP){
		quad_counter = 0;
	}*/
	//--------------------------------------------------------------------------

	switch (app->render->curs_anim)
	{
	case 1:
		cursor_animation = cursor_animation_left;
		break;
	case 2:
		cursor_animation = cursor_animation_right;
		break;
	case 3:
		cursor_animation = cursor_animation_up;
		break;
	case 4:
		cursor_animation = cursor_animation_down;
		break;
	default:
		cursor_animation = cursor_animation_idle;
	}

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
			rectangle rect_map_camera_parent = rectangle_map_camera->parent->getScreenRect();
			if (pos_rect.x + rectangle_map_camera->getScreenRect().w <= rect_map_camera_parent.x + rect_map_camera_parent.w
				&& pos_rect.y + rectangle_map_camera->getScreenRect().h < rect_map_camera_parent.y + rect_map_camera_parent.h)
				rectangle_map_camera->setLocalPos(pos_rect.x - rectangle_map_camera->parent->getLocalPos().x, pos_rect.y - rectangle_map_camera->parent->getLocalPos().y);
		}
	}
	
}