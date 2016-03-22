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

void Gui_Elements::SetLocalPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Gui_Elements::Center()
{
	int frame_w = (parent) ? parent->GetLocalRect().w : app->render->camera.w;
	int frame_h = (parent) ? parent->GetLocalRect().h : app->render->camera.h;

	SetLocalPos(frame_w / 2 - rect.w / 2, frame_h / 2 - rect.h / 2);
}

void Gui_Elements::SetSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

rectangle Gui_Elements::GetLocalRect() const
{
	return rect;
}

rectangle Gui_Elements::GetScreenRect() const
{
	if (parent != nullptr)
	{
		iPoint p = GetScreenPos();
		return{ p.x, p.y, rect.w, rect.h };
	}
	return rect;
}

iPoint Gui_Elements::GetScreenPos() const
{
	if (parent != nullptr)
		return parent->GetScreenPos() + iPoint(rect.x, rect.y);
	else
		return iPoint(rect.x, rect.y);
}

iPoint Gui_Elements::GetLocalPos() const
{
	return iPoint(rect.x, rect.y);
}

void Gui_Elements::DebugDraw() const
{
	rectangle r = GetScreenRect();
	app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, false);
}

void Gui_Elements::SetListener(Module* module)
{
	if (listener != nullptr)
		listener->OnGui(this, GuiEvents::listening_ends);

	listener = module;
}

Module* Gui_Elements::Get_Listener()const
{
	return listener;
}

void Gui_Elements::CheckInput(const Gui_Elements* mouse_hover, const Gui_Elements* focus)
{
	bool inside = (mouse_hover == this);

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			listener->OnGui(this, (inside) ? GuiEvents::mouse_enters : GuiEvents::mouse_leaves);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
				listener->OnGui(this, GuiEvents::mouse_lclick_down);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
				listener->OnGui(this, GuiEvents::mouse_lclick_up);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN)
				listener->OnGui(this, GuiEvents::mouse_rclick_down);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_UP)
				listener->OnGui(this, GuiEvents::mouse_lclick_up);
		}

		if (draggable == true && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		{
			iPoint p = GetLocalPos();
			iPoint motion;
			motion = app->input->getMouseMotion();
			SetLocalPos(p.x + motion.x, p.y + motion.y);
		}
	}

	if (have_focus != (focus == this))
	{
		if (listener != nullptr)
		{
			if (focus == this)
				listener->OnGui(this, GuiEvents::gain_focus);
			else
				listener->OnGui(this, GuiEvents::lost_focus);
		}
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
			listener->OnGui(this, GuiEvents::mouse_lclick_down);

		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_UP)
			listener->OnGui(this, GuiEvents::mouse_lclick_up);
	}
}

GuiTypes Gui_Elements::Get_Type()const
{
	return type;
}

// class GuiImage ---------------------------------------------------
GuiImage::GuiImage(const SDL_Texture* texture) : Gui_Elements(), texture(texture)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	SetSize(section.w, section.h);
	type = GuiTypes::image;
}

// --------------------------
GuiImage::GuiImage(const SDL_Texture* texture, const rectangle& section) : Gui_Elements(), texture(texture), section(section)
{
	SetSize(section.w, section.h);
}

// --------------------------
GuiImage::~GuiImage()
{}

// --------------------------
void GuiImage::SetSection(const rectangle& section)
{
	this->section = section;
}

// --------------------------
void GuiImage::Draw() const
{
	iPoint p = GetScreenPos();
	if (parent && parent->cut_childs)
	{
		rectangle r = parent->GetScreenRect();
		app->render->SetViewPort({ r.x, r.y, r.w, r.h });
		p = GetLocalPos();
	}
	app->render->blit(texture, p.x, p.y, (SDL_Rect*)&section, 0.0f);

	if (parent && parent->cut_childs)
		app->render->ResetViewPort();
}
//---------------------------------------

Gui::Gui() : Module()
{
	name.assign("gui");
	//debug = true;
}

// Destructor
Gui::~Gui()
{}

// Called before render is available
bool Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name.assign(conf.child("atlas").attribute("file").as_string());

	return ret;
}

// Called before the first frame
bool Gui::Start()
{
	atlas = app->tex->loadTexture(atlas_file_name.data());

	return true;
}

// Update all guis
bool Gui::PreUpdate()
{
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	const Gui_Elements* mouse_hover = FindMouseHover();
	if (mouse_hover &&
		mouse_hover->can_focus == true &&
		app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
		focus = mouse_hover;

	

	// if TAB find the next item and give it the focus
	if (app->input->getKey(SDL_SCANCODE_TAB) == KeyState::KEY_DOWN)
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
			for (list<Gui_Elements*>::iterator node = elements.begin(); node != elements.end() && i <= pos; node++, i++)
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
				for (list<Gui_Elements*>::iterator node = item->begin(); node != item->end(); node++, i++)
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
	}

	// Now the iteration for input and update
	for (list<Gui_Elements*>::iterator node = elements.begin(); *node; node++)
	{
		Gui_Elements* gui_test = *node;
		if (gui_test->interactive == true)
			gui_test->CheckInput(mouse_hover, focus);
	}
		

	for (list<Gui_Elements*>::iterator node = elements.begin(); *node; node++)
	{
		Gui_Elements* gui_test = *node;
		gui_test->Update(mouse_hover, focus);
	}
		

	return true;
}

// Called after all Updates
const Gui_Elements* Gui::FindMouseHover()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);

	elements.reverse();

	for (list<Gui_Elements*>::iterator item = elements.begin(); *item; item++)
	{
		Gui_Elements* gui_test = *item;
		if (gui_test->interactive == true)
		{
			if (gui_test->GetScreenRect().Contains(mouse.x, mouse.y))
			{
				elements.reverse();
                return gui_test;
			}
				
		}
	}

	elements.reverse();
	return nullptr;
}

// Called after all Updates
bool Gui::PostUpdate()
{
	list<Gui_Elements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
	{
		Gui_Elements* gui = *item;
		if (gui->draw == true)
			gui->Draw();

		if (debug == true && gui->draw == true)
			gui->DebugDraw();
	}

	return true;
}

// Called before quitting
bool Gui::CleanUp()
{
	LOG("Freeing GUI");

	list<Gui_Elements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
		RELEASE(*item);

	elements.clear();

	return true;
}

// Create a simple image
GuiImage* Gui::CreateImage(const char* filename)
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
GuiImage* Gui::CreateImage(const rectangle& section)
{
	GuiImage* ret = NULL;

	ret = new GuiImage(atlas, section);
	elements.push_back(ret);

	return ret;
}



// const getter for atlas
const SDL_Texture* Gui::GetAtlas() const
{
	return atlas;
}



