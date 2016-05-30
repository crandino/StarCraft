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
#include "ShortcutsManager.h"
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
	app->gui->controls_button->enable_element();

	app->gui->controls_panel->disable_element();
	app->gui->ok_controls_button->disable_element();

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
	app->gui->controls_button->disable_element();
	app->gui->controls_panel->disable_element();
	app->gui->ok_controls_button->disable_element();
	return true;
}

void MenuScene::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == app->gui->start_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->start_button->setSection({ 229, 493, 166, 43 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->start_button->setSection({ 35, 493, 166, 43 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->start_button->setSection({ 422, 493, 166, 43 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->start_button->setSection({ 35, 493, 166, 43 });
			app->fade_to_black->fadeToBlack(this, (Module*)app->scene, 3.0f);
			break;
		}
	}

	if (ui == app->gui->close_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->close_button->setSection({ 229, 593, 166, 43 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->close_button->setSection({ 35, 593, 166, 43 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->close_button->setSection({ 422, 593, 166, 43 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->close_button->setSection({ 35, 593, 166, 43 });
			app->closeApp();
			break;
		}
	}

	if (ui == app->gui->controls_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->controls_button->setSection({ 229, 543, 166, 43 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->controls_button->setSection({ 35, 543, 166, 43 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->controls_button->setSection({ 422, 543, 166, 43 });
			app->gui->controls_panel->enable_element();
			app->gui->ok_controls_button->enable_element();
			app->gui->start_button->interactive = false;
			app->gui->close_button->interactive = false;
			app->gui->controls_button->interactive = false; 
			app->shortcuts->showShortcuts();
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->controls_button->setSection({ 35, 543, 166, 43 });
			break;
		}
	}

	if (ui == app->gui->ok_controls_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			app->gui->ok_controls_button->setSection({ 859, 369, 141, 41 });
			break;
		case(MOUSE_LEAVES) :
			app->gui->ok_controls_button->setSection({ 665, 369, 141, 41 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			app->gui->ok_controls_button->setSection({ 1052, 369, 141, 41 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->gui->ok_controls_button->setSection({ 665, 369, 141, 41 });
			app->gui->ok_controls_button->disable_element();
			app->gui->controls_panel->disable_element();
			app->shortcuts->hideShortcuts();
			app->gui->start_button->interactive = true;
			app->gui->close_button->interactive = true;
			app->gui->controls_button->interactive= true;
			break;
		}
	}
}