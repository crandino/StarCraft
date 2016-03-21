#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Gui.h"
#include "Scene.h"

Gui::Gui() : Module()
{
	name.assign("gui");
}

// Destructor
Gui::~Gui()
{}

// Called before render is available
bool Gui::awake(pugi::xml_node& conf)
{
	bool ret = true;
	return ret;
}

// Called before the first frame
bool Gui::start()
{
	mouse_texture = app->tex->loadTexture("cursor.png");
	mouse = new Cursor(mouse_texture);

	SDL_ShowCursor(SDL_DISABLE); // Hidding mouse cursor

	return true;
}

// Update all guis
bool Gui::preUpdate()
{

	return true;
}

// Called after all Updates
bool Gui::postUpdate()
{
	return true;
}

// Called before quitting
bool Gui::cleanUp()
{
	delete mouse;
	app->tex->unloadTexture(mouse_texture);

	return true;
}

//UI Element-------------------------------------------------------------

void UI_Element::draw(){}
void UI_Element::interact(MouseEvents events){}

void UI_Element::debug(bool focus){
	if (!focus)
		app->render->DrawQuad(*box, 255, 255, 0, 255, false);
	else
		app->render->DrawQuad(*box, 0, 0, 255, 255, false);
}

void UI_Element::drag()
{
	iPoint mouseMotion = app->input->getMouseMotion();
	box->x = box->x + mouseMotion.x;
	box->y = box->y + mouseMotion.y;
}

//Cursor
Cursor::Cursor(SDL_Texture* texture)
{
	this->texture = texture;
	position.x = 0;
	position.y = 0;
}
void Cursor::setPosition(iPoint coords)
{
	position.x = coords.x;
	position.y = coords.y;
}
void Cursor::updatePosition()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);
	mouse.x += app->render->camera.x;
	mouse.y += app->render->camera.y;
	setPosition(mouse);
}
void Cursor::draw(){
	app->render->blit(texture, position.x, position.y, false);
}
//---------------------------------------