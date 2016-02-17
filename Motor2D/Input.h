#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"
#include "Point2d.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class Input : public Module
{

public:

	Input();

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before the first frame
	bool start();

	// Called each loop iteration
	bool preUpdate();

	// Called before quitting
	bool cleanUp();

	// Gather relevant win events
	bool getWindowEvent(EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	KeyState getKey(int id) const
	{
		return keyboard[id];
	}

	KeyState getMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check if a certain window event happened
	bool getWindowEvent(int code);

	// Get mouse / axis position
	void getMousePosition(iPoint &p) const;
	iPoint getMouseMotion();

private:

	bool		windowEvents[WE_COUNT];
	KeyState	*keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
	
};

#endif // __INPUT_H__
