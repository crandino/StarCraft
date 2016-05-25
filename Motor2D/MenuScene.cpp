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
			case(MOUSE_LCLICK_DOWN) :
			app->gui->start_button->setSection({ 339, 103, 141, 38 });
			break;

		case(MOUSE_LCLICK_UP) :
			app->gui->start_button->setSection({ 339, 164, 141, 39 });
			app->fade_to_black->fadeToBlack(this, (Module*)app->scene, 3.0f);
			break;
		}
	}

	if (ui == app->gui->close_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			//app->audio->playFx(fx_click, 0);
			app->gui->close_button->setSection({ 339, 278, 145, 40 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->close_button->setSection({ 339, 229, 145, 40 });
			app->closeApp();
			break;
		}
	}
}