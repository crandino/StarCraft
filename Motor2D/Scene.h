#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
using namespace std;

struct SDL_Texture;
class GuiImage;
class GuiCursor;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

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

	//HUD UI
	GuiImage* ui_terran = nullptr;
	GuiImage* rectangle_map_camera = nullptr;
	GuiImage* rectangle_map = nullptr;

	//MOUSE UI
	GuiCursor* mouse = nullptr;
	SDL_Texture* mouse_texture = nullptr;

public:
	//Provisional------------------------------
	//Mouse quad stuff
	int quad_counter = 0;
	iPoint init_mouse;
	SDL_Rect selection;
	//-----------------------------------------

	Animation* idle;
	vector<Animation*> animation_set;
};

#endif // __SCENE_H__
