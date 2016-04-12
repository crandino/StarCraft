#ifndef __GUIELEMENTS_H__
#define __GUIELEMENTS_H__

#include "Gui.h"

class GuiElements
{

public:
	GuiElements();
	virtual ~GuiElements()
	{}

	virtual void draw() const
	{}
	virtual void debugDraw() const;
	virtual void update(const GuiElements* mouse_hover, const GuiElements* focus)
	{}
	virtual void update()
	{}
	void checkInput(const GuiElements* mouse_hover, const GuiElements* focus);
	void setLocalPos(int x, int y);
	void center();
	SDL_Rect getScreenRect() const;
	SDL_Rect getLocalRect() const;
	iPoint getScreenPos() const;
	iPoint getLocalPos() const;
	void setListener(Module* module);
	GUI_TYPES getType()const;
	Module* getListener()const;

protected:
	void setSize(int w, int h);

public:
	bool draggable = false;
	bool interactive = false;
	bool cut_childs = false;
	bool can_focus = false;
	bool draw_element = true;
	GuiElements* parent = nullptr;
protected:
	GUI_TYPES type = UNKNOWN;
	Module* listener = nullptr;
	bool have_focus = false;
private:
	bool mouse_inside = false;
	SDL_Rect rect;
};

#endif !__GUIELEMENTS_H__
