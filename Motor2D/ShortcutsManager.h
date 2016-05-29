#ifndef __SHORTCUTS_MANAGER_H__
#define __SHORTCUTS_MANAGER_H__

#include "Module.h"
#include <string>
#include <list>

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

	bool isCommandActive(const char *command_to_check);

	void showShortcuts();
	void hideShortcuts();

	// Only active when controls menu is displayed
	bool			change_on_command;
	const char*     new_command = NULL;
	
public:

	//Shortcuts list
	list<ShortCut*>			shortcuts_list;

	//Shortcuts xml file path
	string					inputs_file_path;

	//Shortcuts UI management
	GuiImage*				pop_up = nullptr;
	void onGui(GuiElements* gui, GUI_EVENTS event);
};

#endif