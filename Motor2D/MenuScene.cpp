#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "MenuScene.h"
#include "GuiImage.h"
#include "GuiLabel.h"

MenuScene::MenuScene()
{
	name.assign("menu_scene");
}

MenuScene::~MenuScene()
{

}

bool MenuScene::awake(pugi::xml_node &node)
{
	LOG("Loading Menu Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool MenuScene::start()
{
	return true;
}

// Called each loop iteration
bool MenuScene::preUpdate()
{
	return true;
}

// Called each loop iteration
bool MenuScene::update(float dt)
{
	return true;
}

// Called each loop iteration
bool MenuScene::postUpdate()
{
	bool ret = true;
	return ret;
}

bool MenuScene::cleanUp()
{
	LOG("Freeing Menu Scene");
	return true;
}

void MenuScene::onGui(GuiElements* ui, GUI_EVENTS event)
{
	
}