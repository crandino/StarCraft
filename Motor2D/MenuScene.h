#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "Module.h"
#include "Animation.h"
#include <vector>

struct SDL_Texture;
class GuiImage;
class GuiLabel;

class MenuScene : public Module
{
public:

	MenuScene();

	// Destructor
	virtual ~MenuScene();

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
};


#endif //!__MENUSCENE_H__