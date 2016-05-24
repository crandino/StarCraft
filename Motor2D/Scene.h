#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
using namespace std;

struct SDL_Texture;
class GuiImage;
class GuiLabel;

class Scene : public Module
{
public:

	Scene(bool enabled);

	// Destructor
	~Scene();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before the first frame
	bool start();

	// Called before all updates
	bool preUpdate();

	// Called each loop iteration
	bool update(float dt);

	// Called before all updates
	bool postUpdate();

	// Called before quitting
	bool cleanUp();
	//GUI
	void onGui(GuiElements* ui, GUI_EVENTS event);

private:

	bool debug = false;

	//HUD UI
	
	GuiImage* rectangle_map_camera = nullptr;
	GuiImage* rectangle_map = nullptr;
	GuiImage* start_menu = nullptr;

	//ROF
	SDL_Texture* start_menu_img = nullptr;

	// FogOfWar Timer
	// This timer will clean the fog of war 3 times per second.
	Timer fog_of_war_timer;

public:
   
	//GuiImage* ui_terran = nullptr;
	// CRZ PathFinding tests
	/*SDL_Texture *path_tile;
	bool	     path_selected;
	iPoint		 start_position, final_position;*/

};

#endif // __SCENE_H__
