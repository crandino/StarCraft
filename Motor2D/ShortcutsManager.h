#ifndef __SHORTCUTS_MANAGER_H__
#define __SHORTCUTS_MANAGER_H__

#include "Module.h"
#include <string>
#include <list>
#include <map>

using namespace std;

class GuiElements;
class GuiLabel;
class GuiImage;

enum INPUT_TYPE
{
	DOWN,
	UP,
	REPEAT
};

enum ACTIONS
{
	FOCUS_ATTACK,
	LOCATE_JIM_RAYNOR,
	LOCATE_COMMAND_CENTER,
	LOCATE_LAST_ATTACK_POSITION,
	SAVE_GAME,
	LOAD_GAME
};

struct ShortCut
{
	ShortCut()
	{}

	ShortCut(INPUT_TYPE _type, string _name, string _command)
	{
		type = _type;
		name = _name;
		command = _command;
	}

	INPUT_TYPE	 type;
	ACTIONS		 action;
	bool		 active;
	bool		 ready_to_change = false;
	string		 name;
	string		 command;	

	GuiLabel*	 command_label = nullptr;
	GuiLabel*	 shortcut_label = nullptr;
};

class ShortcutsManager : public Module
{
public:

	ShortcutsManager(bool enabled);

	// Destructor
	virtual ~ShortcutsManager();

	// Called when before render is available
	bool awake(pugi::xml_node&);

	// Call before first frame
	bool start();

	// Called before all Updates
	bool preUpdate();

	bool update(float dt);

	// Called after all Updates
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	//Refresh commands once have been changed
	void changeShortcutCommand(ShortCut* shortcut);

	bool isCommandActive(ACTIONS action);

	void showShortcuts();
	void hideShortcuts();

	// Only active when controls menu is displayed
	bool			change_on_command;
	const char*     new_command = NULL;
	
public:

	map<string, ACTIONS>    action_resolver;
	map<string, INPUT_TYPE> input_type_resolver;
	map<string, ACTIONS>    key_to_action;

	//Shortcuts list
	list<ShortCut*>			shortcuts_list;

	//Shortcuts xml file path
	string					inputs_file_path;

	//Shortcuts UI management
	GuiImage*				pop_up = nullptr;
	void onGui(GuiElements* gui, GUI_EVENTS event);
};

#endif