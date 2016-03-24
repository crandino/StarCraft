#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;
class GuiImage;


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
	void onGui(Gui_Elements* ui, GuiEvents event);

private:

	GuiImage* ui_terran;
	GuiImage* rectangle_map_camera;
	GuiImage* rectangle_map;

};

#endif // __SCENE_H__
