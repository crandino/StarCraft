#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Input.h"
#include "Audio.h"
#include "Render.h"
#include "MenuScene.h"
#include "GuiImage.h"
#include "GuiLabel.h"
#include "Textures.h"
#include "GameManager.h"
#include "FadeToBlack.h"

MenuScene::MenuScene(bool enabled) : Module(enabled)
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
	app->gui->background->enable_element();
	app->gui->start_button->enable_element();
	app->gui->close_button->enable_element();

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
	app->gui->background->disable_element();
	app->gui->start_button->disable_element();
	app->gui->close_button->disable_element();
	return true;
}

void MenuScene::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == app->gui->start_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->start_button->setSection({ 416, 507, 143, 41 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->start_button->setSection({ 45, 507, 143, 41 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->start_button->setSection({ 233, 507, 143, 41 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->start_button->setSection({ 45, 507, 143, 41 });
			app->fade_to_black->fadeToBlack(this, (Module*)app->scene, 3.0f);
			break;
		}
	}

	if (ui == app->gui->close_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->close_button->setSection({ 416, 573, 143, 41 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->close_button->setSection({ 45, 573, 143, 41 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->close_button->setSection({ 233, 573, 143, 41});
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->close_button->setSection({ 45, 573, 143, 41 });
			app->closeApp();
			break;
		}
	}
}