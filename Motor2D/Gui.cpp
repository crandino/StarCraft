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
GuiElements::GuiElements() : rect({ 0, 0, 0, 0 })
{
}

void GuiElements::setLocalPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void GuiElements::center()
{
	int frame_w = (parent) ? parent->getLocalRect().w : app->render->camera.w;
	int frame_h = (parent) ? parent->getLocalRect().h : app->render->camera.h;

	setLocalPos(frame_w / 2 - rect.w / 2, frame_h / 2 - rect.h / 2);
}

void GuiElements::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

rectangle GuiElements::getLocalRect() const
{
	return rect;
}

rectangle GuiElements::getScreenRect() const
{
	if (parent != nullptr)
	{
		iPoint p = getScreenPos();
		return{ p.x, p.y, rect.w, rect.h };
	}
	return rect;
}

iPoint GuiElements::getScreenPos() const
{
	if (parent != nullptr)
		return parent->getScreenPos() + iPoint(rect.x, rect.y);
	else
		return iPoint(rect.x, rect.y);
}

iPoint GuiElements::getLocalPos() const
{
	return iPoint(rect.x, rect.y);
}


void GuiElements::debugDraw() const
{
	rectangle r = getScreenRect();
	if (this->getType() == CURSOR)
		app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, true);
	else
	    app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, false);
	
}

void GuiElements::setListener(Module* module)
{
	if (listener != nullptr)
		listener->onGui(this, LISTENING_ENDS);

	listener = module;
}

Module* GuiElements::getListener()const
{
	return listener;
}

void GuiElements::checkInput(const GuiElements* mouse_hover, const GuiElements* focus)
{
	bool inside = (mouse_hover == this);

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			listener->onGui(this, (inside) ? MOUSE_ENTERS : MOUSE_LEAVES);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
				listener->onGui(this, MOUSE_LCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				listener->onGui(this, MOUSE_LCLICK_DOWN_REPEAT);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				listener->onGui(this, MOUSE_LCLICK_UP);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
				listener->onGui(this, MOUSE_RCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_UP)
				listener->onGui(this, MOUSE_RCLICK_UP);
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
				listener->onGui(this, GAIN_FOCUS);
			else
				listener->onGui(this, LOST_FOCUS);
		}
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
			listener->onGui(this, MOUSE_LCLICK_DOWN);

		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_UP)
			listener->onGui(this, MOUSE_LCLICK_UP);
	}
}

GUI_TYPES GuiElements::getType()const
{
	return type;
}

// CLASS GuiImage ---------------------------------------------------
GuiImage::GuiImage(const SDL_Texture* texture) : GuiElements(), texture(texture)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	setSize(section.w, section.h);
	type = IMAGE;
}

// --------------------------
GuiImage::GuiImage(const SDL_Texture* texture, const rectangle& section) : GuiElements(), texture(texture), section(section)
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
GuiCursor::GuiCursor(const SDL_Texture* texture, Animation* animation) : GuiElements(), texture(texture), cursor_anim(animation)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	setSize(section.w, section.h);
	type = CURSOR;
}

GuiCursor::~GuiCursor(){

}

void GuiCursor::setPosition(iPoint coords)
{
	position.x = coords.x;
	position.y = coords.y;
	iPoint position_debug_draw = app->render->screenToWorld(position.x, position.y);
	setLocalPos(position_debug_draw.x, position_debug_draw.y);
}
void GuiCursor::updatePosition()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);
	setPosition(mouse);
}

void GuiCursor::setTexture(SDL_Texture* tmp_texture)
{
	texture = tmp_texture;
}

void GuiCursor::draw()const
{
	//iPoint pos = getScreenPos();
	//app->render->blit(texture, position.x, position.y, (SDL_Rect*)&section, 0.0f);
	app->render->blit(texture, position.x, position.y, &(cursor_anim->getCurrentFrame()), 0.0f);
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

	return true;
}

// Update all guis
bool Gui::preUpdate()
{

	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	const GuiElements* mouse_hover = findMouseHover();
	if (mouse_hover &&
		mouse_hover->can_focus == true &&
		app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
		focus = mouse_hover;

	
	// if TAB find the next item and give it the focus
	/*if (app->input->getKey(SDL_SCANCODE_TAB) == KeyState::KEY_DOWN)
	{   list<GuiElements*>* item = NULL;
		//int pos = elements.find((GuiElements*)focus);
		int pos = 0;
		for (list<GuiElements*>::iterator node = elements.begin(); *node && *node != (GuiElements*)focus; node++)
		{
			pos++;
		}

		if (pos > 0)
		{
			focus = nullptr;
			//item = elements.At(pos);
			int i = 0;
			for (list<GuiElements*>::iterator node = elements.begin(); *node && i <= pos; node++, i++)
			{
				if (i == pos)
				{
					i = 0;
					GuiElements* gui_test = *node;
					item->push_back(gui_test);
				}
			}

			if (item)
			{
				for (list<GuiElements*>::iterator node = item->begin(); *node; node++, i++)
				{
					if (i == pos)
					{
						node++;
						item->push_back(*node);
					}
				}
			}

			for (list<GuiElements*>::iterator node = item->begin(); *node; node++)
			{
				GuiElements* gui_test = *node;
				if (gui_test->can_focus == true)
				{
					focus = gui_test;
					break;
				}
			}
				
		}
		if (focus == nullptr)
		{
			for (list<GuiElements*>::iterator node = elements.begin(); *node; node++)
			{
				GuiElements* gui_test = *node;
				if (gui_test->can_focus == true)
				{
					focus = gui_test;
					break;
				}
			}
		}
	}*/

	// Now the iteration for input and update
	for (list<GuiElements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		GuiElements* gui_test = *node;
		if (gui_test->interactive == true)
		    gui_test->checkInput(mouse_hover, focus);
	}
		

	for (list<GuiElements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		GuiElements* gui_test = *node;
		gui_test->update(mouse_hover, focus);
		if (gui_test->getType() == CURSOR)
		{
			gui_test->updatePosition();
		}
	}

	
	return true;
}



// Called after all Updates
bool Gui::postUpdate()
{
	list<GuiElements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
	{
		GuiElements* gui = *item;
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

	list<GuiElements*>::iterator item;

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
GuiCursor* Gui::createCursor(const SDL_Texture* texture, Animation* animation){

	GuiCursor* ret = NULL;

	ret = new GuiCursor(texture, animation);
	elements.push_back(ret);
	
	return ret;
}

//
SDL_Rect Gui::mouseQuad(iPoint init_mouse)
{
	iPoint current_mouse;
	app->input->getMousePosition(current_mouse);
	SDL_Rect rect = { init_mouse.x, init_mouse.y, current_mouse.x - init_mouse.x, current_mouse.y - init_mouse.y };
	app->render->DrawQuad(rect, 65, 105, 225, 100, true, false);
	return rect;
}

// Called after all Updates
const GuiElements* Gui::findMouseHover()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);

	elements.reverse();

	for (list<GuiElements*>::iterator item = elements.begin(); item != elements.end(); item++)
	{
		GuiElements* gui_test = *item;
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




