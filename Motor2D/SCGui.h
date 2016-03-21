#include "App.h"
#include "Module.h"
#include "Render.h"

#include <string>
#include <list>

#define CURSOR_WIDTH 2

enum MouseEvents{
	MouseEnter,
	MouseOut,
	MouseRightClick,
	MouseLeftClick,
};

enum ElementType{
	cursor,
};

class UI_Element{

public:
	UI_Element(){};
	~UI_Element(){};
public:

	ElementType type;
	SDL_Rect* box;
	SDL_Texture*  texture;
	iPoint position;

	bool listener = false;
	bool focused = false;

	virtual void draw();
	virtual void interact(MouseEvents events);
	virtual void drag();
	void debug(bool focus);
};

class Cursor : public UI_Element{
public:

	Cursor(SDL_Texture* texture);
	~Cursor(){};

	void setPosition(iPoint coords);
	void updatePosition();
	void draw();
};

//-----------------------------------------------------------------------
//CLASS GUI
class SCGui : public Module
{
public:

	SCGui();

	// Destructor
	virtual ~SCGui();

	// Called when before render is available
	bool awake(pugi::xml_node&);

	// Call before first frame
	bool start();

	// Called before all Updates
	bool preUpdate();

	// Called after all Updates
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	bool checkMousePosition(iPoint mousePosition, UI_Element* tmp);

	bool guiEvents(UI_Element* trigger, MouseEvents events);

private:

	bool debug = false;

public:

	list<UI_Element*> elements;
	list<UI_Element*> inputs;

	//Cursor
	Cursor* mouse;
	SDL_Texture* mouse_texture;
};