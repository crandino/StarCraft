#ifndef __GUI_H__
#define __GUI_H__

#include "App.h"
#include "Module.h"
#include "Render.h"
#include "Point2d.h"
#include "p2Defs.h"
#include <string>
#include <list>

#define CURSOR_WIDTH 2
using namespace std;

enum GuiEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit,
	value_changed,
	save_pos_thumb,
	load_pos_thumb,
};

enum GuiTypes
{
	unknown,
	image,
	label,
	button,
	hscrollbar,
	hscrollbarvertical
};

// ---------------------------------------------------
class Gui_Elements
{
public:
	Gui_Elements();
	virtual ~Gui_Elements()
	{}

	virtual void Draw() const
	{}
	virtual void DebugDraw() const;
	virtual void Update(const Gui_Elements* mouse_hover, const Gui_Elements* focus)
	{}
	void CheckInput(const Gui_Elements* mouse_hover, const Gui_Elements* focus);
	void SetLocalPos(int x, int y);
	void Center();
	rectangle GetScreenRect() const;
	rectangle GetLocalRect() const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	void SetListener(Module* module);
	GuiTypes Get_Type()const;
	Module* Get_Listener()const;

protected:
	void SetSize(int w, int h);

public:
	bool draggable = false;
	bool interactive = false;
	bool cut_childs = false;
	bool can_focus = false;
	bool draw = true;
	Gui_Elements* parent = nullptr;
protected:
	GuiTypes type = GuiTypes::unknown;
	Module* listener = nullptr;
	bool have_focus = false;
private:
	bool mouse_inside = false;
	rectangle rect;
};

// ---------------------------------------------------
class GuiImage : public Gui_Elements
{
public:
	GuiImage(const SDL_Texture* texture);
	GuiImage(const SDL_Texture* texture, const rectangle& section);
	~GuiImage();

	void SetSection(const rectangle& section);
	void Draw() const;

private:

	rectangle section;
	const SDL_Texture* texture = nullptr;
};

// ---------------------------------------------------
class GuiCursor : public Gui_Elements
{
public:
	GuiCursor(const SDL_Texture* texture);
	~GuiCursor();

	void SetPosition(iPoint coords);
	void UpdatePosition();
	void Draw();

private:

	const SDL_Texture* texture = nullptr;
	iPoint position;
};
	

//-----------------------------------------------------------------------
//CLASS GUI

struct SDL_Texture;

// ---------------------------------------------------
class Gui : public Module
{
public:

	Gui();

	// Destructor
	virtual ~Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	GuiImage* CreateImage(const char* filename);
	GuiImage* CreateImage(const SDL_Texture* texture, const rectangle& atlas_section);
	GuiCursor* CreateCursor(const SDL_Texture* texture);
	/*GuiLabel* CreateLabel(const char* text);
	GuiHScrollBar* CreateHScrollBar(const rectangle& bar, const rectangle& thumb, const rectangle& bar_offset = { 0, 0, 0, 0 }, const iPoint& thumb_margins = { 0, 0 });
	GuiHScrollBarVertical* CreateHScrollBarVertical(const rectangle& bar, const rectangle& thumb, const rectangle& bar_offset = { 0, 0, 0, 0 }, const iPoint& thumb_margins = { 0, 0 });*/

	const Gui_Elements* FindMouseHover();
	const SDL_Texture* GetAtlas() const;

private:

	bool debug = false;
	list<Gui_Elements*> elements;
	const Gui_Elements* focus = nullptr;
	SDL_Texture* atlas = nullptr;
	string atlas_file_name;

	//Cursor
	GuiCursor* mouse = nullptr;
	SDL_Texture* mouse_texture = nullptr;
};

#endif