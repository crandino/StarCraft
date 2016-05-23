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
	background = app->gui->createImage("UI/Screens/menu_image.png");
	background->enable_element();
	background->center();

	start_image = app->tex->loadTexture("UI/Screens/Start_Image.png");

	start_button = app->gui->createImage(start_image, { 339, 164, 141, 39 });
	start_button->parent = background;
	start_button->setLocalPos(50, 200);
	start_button->enable_element();
	start_button->can_focus = true;
	start_button->setListener(this);

	close_button = app->gui->createImage(start_image, { 339, 229, 141, 39 });
	close_button->parent = background;
	close_button->setLocalPos(50, 250);
	close_button->enable_element();
	close_button->can_focus = true;
	close_button->setListener(this);

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
	background->disable_element();
	start_button->disable_element();
	close_button->disable_element();
	return true;
}

void MenuScene::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == start_button)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			start_button->setSection({ 339, 103, 141, 38 });
			break;

		case(MOUSE_LCLICK_UP) :
			start_button->setSection({ 339, 164, 141, 39 });
			app->fade_to_black->fadeToBlack(this, (Module*)app->scene, 3.0f);
			break;
		}
	}

	if (ui == close_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			//app->audio->playFx(fx_click, 0);
			close_button->setSection({ 339, 278, 145, 40 });
			break;
		case(MOUSE_LCLICK_UP) :
			close_button->setSection({ 339, 229, 145, 40 });
			app->game_manager->endGame();
			break;
		}
	}
}