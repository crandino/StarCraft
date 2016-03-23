#include "Textures.h"
#include "App.h"
#include "p2Log.h"
#include "Render.h"
//#include "Fonts.h"
#include "Input.h"
#include "Gui.h"
#include "p2Defs.h"
#include "Textures.h"
#include "SDL/include/SDL.h"

using namespace std;

// class Gui ---------------------------------------------------
Gui_Elements::Gui_Elements() : rect({ 0, 0, 0, 0 })
{
}

void Gui_Elements::setLocalPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Gui_Elements::center()
{
	int frame_w = (parent) ? parent->getLocalRect().w : app->render->camera.w;
	int frame_h = (parent) ? parent->getLocalRect().h : app->render->camera.h;

	setLocalPos(frame_w / 2 - rect.w / 2, frame_h / 2 - rect.h / 2);
}

void Gui_Elements::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

rectangle Gui_Elements::getLocalRect() const
{
	return rect;
}

rectangle Gui_Elements::getScreenRect() const
{
	if (parent != nullptr)
	{
		iPoint p = getScreenPos();
		return{ p.x, p.y, rect.w, rect.h };
	}
	return rect;
}

iPoint Gui_Elements::getScreenPos() const
{
	if (parent != nullptr)
		return parent->getScreenPos() + iPoint(rect.x, rect.y);
	else
		return iPoint(rect.x, rect.y);
}

iPoint Gui_Elements::getLocalPos() const
{
	return iPoint(rect.x, rect.y);
}

void Gui_Elements::debugDraw() const
{
	rectangle r = getScreenRect();
	app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, false);
}

void Gui_Elements::setListener(Module* module)
{
	if (listener != nullptr)
		listener->OnGui(this, GuiEvents::LISTENING_ENDS);

	listener = module;
}

Module* Gui_Elements::get_Listener()const
{
	return listener;
}

void Gui_Elements::checkInput(const Gui_Elements* mouse_hover, const Gui_Elements* focus)
{
	bool inside = (mouse_hover == this);

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			listener->OnGui(this, (inside) ? GuiEvents::MOUSE_ENTERS : GuiEvents::MOUSE_LEAVES);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
				listener->OnGui(this, GuiEvents::MOUSE_LCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				listener->OnGui(this, GuiEvents::MOUSE_LCLICK_UP);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
				listener->OnGui(this, GuiEvents::MOUSE_RCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_UP)
				listener->OnGui(this, GuiEvents::MOUSE_RCLICK_UP);
		}

		if (draggable == true && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		{
			iPoint p = getLocalPos();
			iPoint motion;
			motion = app->input->getMouseMotion();
			setLocalPos(p.x + motion.x, p.y + motion.y);
		}
	}

	if (have_focus != (focus == this))
	{
		if (listener != nullptr)
		{
			if (focus == this)
				listener->OnGui(this, GuiEvents::GAIN_FOCUS);
			else
				listener->OnGui(this, GuiEvents::LOST_FOCUS);
		}
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
			listener->OnGui(this, GuiEvents::MOUSE_LCLICK_DOWN);

		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_UP)
			listener->OnGui(this, GuiEvents::MOUSE_LCLICK_UP);
	}
}

GuiTypes Gui_Elements::get_Type()const
{
	return type;
}

// CLASS GuiImage ---------------------------------------------------
GuiImage::GuiImage(const SDL_Texture* texture) : Gui_Elements(), texture(texture)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	setSize(section.w, section.h);
	type = GuiTypes::IMAGE;
}

// --------------------------
GuiImage::GuiImage(const SDL_Texture* texture, const rectangle& section) : Gui_Elements(), texture(texture), section(section)
{
	setSize(section.w, section.h);
}

// --------------------------
GuiImage::~GuiImage()
{}

// --------------------------
void GuiImage::setSection(const rectangle& section)
{
	this->section = section;
}

// --------------------------
void GuiImage::draw() const
{
	iPoint p = getScreenPos();
	if (parent && parent->cut_childs)
	{
		rectangle r = parent->getScreenRect();
		app->render->SetViewPort({ r.x, r.y, r.w, r.h });
		p = getLocalPos();
	}
	app->render->blit(texture, p.x, p.y, (SDL_Rect*)&section, 0.0f);

	if (parent && parent->cut_childs)
		app->render->ResetViewPort();
}

//CURSOR------------------------------------------------+//Cursor
GuiCursor::GuiCursor(const SDL_Texture* texture){
	this->texture = texture;
	position.x = 0;
	position.y = 0;
}

GuiCursor::~GuiCursor(){

}

void GuiCursor::setPosition(iPoint coords){
	position.x = coords.x;
	position.y = coords.y;
}
void GuiCursor::updatePosition(){
	iPoint mouse;
	app->input->getMousePosition(mouse);
	setPosition(mouse);
}
void GuiCursor::draw(){
	updatePosition();
	app->render->blit(texture, position.x, position.y, false);
}

//---------------------------------------
//CLASS Gui------------------------------------------------+//

Gui::Gui() : Module()
{
	name.assign("gui");
	//debug = true;
}

// Destructor
Gui::~Gui()
{}

// Called before render is available
bool Gui::awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name.assign(conf.child("atlas").attribute("file").as_string());

	return ret;
}

// Called before the first frame
bool Gui::start()
{
	atlas = app->tex->loadTexture(atlas_file_name.data());

	//Cursor
	mouse_texture = app->tex->loadTexture("cursor2.png");
	mouse = createCursor(mouse_texture);

	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

// Update all guis
bool Gui::preUpdate()
{

	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	const Gui_Elements* mouse_hover = findMouseHover();
	if (mouse_hover &&
		mouse_hover->can_focus == true &&
		app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
		focus = mouse_hover;

	
	// if TAB find the next item and give it the focus
	/*if (app->input->getKey(SDL_SCANCODE_TAB) == KeyState::KEY_DOWN)
	{   list<Gui_Elements*>* item = NULL;
		//int pos = elements.find((Gui_Elements*)focus);
		int pos = 0;
		for (list<Gui_Elements*>::iterator node = elements.begin(); *node && *node != (Gui_Elements*)focus; node++)
		{
			pos++;
		}

		if (pos > 0)
		{
			focus = nullptr;
			//item = elements.At(pos);
			int i = 0;
			for (list<Gui_Elements*>::iterator node = elements.begin(); *node && i <= pos; node++, i++)
			{
				if (i == pos)
				{
					i = 0;
					Gui_Elements* gui_test = *node;
					item->push_back(gui_test);
				}
			}

			if (item)
			{
				for (list<Gui_Elements*>::iterator node = item->begin(); *node; node++, i++)
				{
					if (i == pos)
					{
						node++;
						item->push_back(*node);
					}
				}
			}

			for (list<Gui_Elements*>::iterator node = item->begin(); *node; node++)
			{
				Gui_Elements* gui_test = *node;
				if (gui_test->can_focus == true)
				{
					focus = gui_test;
					break;
				}
			}
				
		}
		if (focus == nullptr)
		{
			for (list<Gui_Elements*>::iterator node = elements.begin(); *node; node++)
			{
				Gui_Elements* gui_test = *node;
				if (gui_test->can_focus == true)
				{
					focus = gui_test;
					break;
				}
			}
		}
	}*/

	// Now the iteration for input and update
	for (list<Gui_Elements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		Gui_Elements* gui_test = *node;
		if (gui_test->interactive == true)
		    gui_test->checkInput(mouse_hover, focus);
	}
		

	for (list<Gui_Elements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		Gui_Elements* gui_test = *node;
		gui_test->update(mouse_hover, focus);
	}

	
	return true;
}



// Called after all Updates
bool Gui::postUpdate()
{
	list<Gui_Elements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
	{
		Gui_Elements* gui = *item;
		if (gui->draw_element == true)
			gui->draw();

		if (debug == true && gui->draw_element == true)
			gui->debugDraw();
	}

	
	return true;
}

// Called before quitting
bool Gui::cleanUp()
{
	LOG("Freeing GUI");

	list<Gui_Elements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
		RELEASE(*item);

	elements.clear();

	return true;
}

// Create a simple image
GuiImage* Gui::createImage(const char* filename)
{
	GuiImage* ret = NULL;
	SDL_Texture* texture = app->tex->loadTexture(filename);

	if (texture != NULL)
	{
		ret = new GuiImage(texture);
		elements.push_back(ret);
	}

	return ret;
}

// Create a simple image
GuiImage* Gui::createImage(const SDL_Texture* texture, const rectangle& section)
{
	GuiImage* ret = NULL;
	if (texture == NULL)
	{
		texture = atlas;
	}
	ret = new GuiImage(texture, section);
	elements.push_back(ret);

	return ret;
}

//Create cursor
GuiCursor* Gui::createCursor(const SDL_Texture* texture){

	GuiCursor* ret = NULL;

	ret = new GuiCursor(mouse_texture);
	elements.push_back(ret);
	
	return ret;
}

// Called after all Updates
const Gui_Elements* Gui::findMouseHover()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);

	elements.reverse();

	for (list<Gui_Elements*>::iterator item = elements.begin(); item != elements.end(); item++)
	{
		Gui_Elements* gui_test = *item;
		if (gui_test->interactive == true)
		{
			if (gui_test->getScreenRect().Contains(mouse.x, mouse.y))
			{
				elements.reverse();
                return gui_test;
			}
				
		}
	}

	elements.reverse();
	return nullptr;
}

// const getter for atlas
const SDL_Texture* Gui::getAtlas() const
{
	return atlas;
}




