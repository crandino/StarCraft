#include "ShortcutsManager.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "App.h"
#include "Input.h"

ShortcutsManager::ShortcutsManager(bool enabled) : Module(enabled)
{
	name.append("shortcuts_manager");
	change_on_command = false;
}

// Destructor
ShortcutsManager::~ShortcutsManager()
{}

// Called when before render is available
bool ShortcutsManager::awake(pugi::xml_node& node)
{
	bool ret = true;

	//Loading shortcuts path xml
	for (node = node.child("shortcut"); node && ret; node = node.next_sibling("shortcut"))
	{
		ShortCut* shortcut = new ShortCut();

		string type_tmp = node.child("TYPE").attribute("value").as_string();
		if (type_tmp == "UP")
			shortcut->type = UP;
		if (type_tmp == "DOWN")
			shortcut->type = DOWN;
		if (type_tmp == "REPEAT")
			shortcut->type = REPEAT;

		shortcut->name = node.child("name").attribute("value").as_string();
		shortcut->command = node.child("command").attribute("value").as_string();

		shortcut->active = false;
		shortcuts_list.push_back(shortcut);
	}

	return ret;
}

// Call before first frame
bool ShortcutsManager::start()
{
	// Now, render is loaded.
	iPoint pos = { 0, 0 };
	for (list<ShortCut*>::iterator it = shortcuts_list.begin(); it != shortcuts_list.end(); ++it)
	{
		(*it)->command_label = app->gui->createLabel((*it)->command.data(), 2);
		(*it)->command_label->setLocalPos(pos.x + 175, pos.y);
		(*it)->command_label->enable_element();
		(*it)->command_label->setListener(this);

		(*it)->shortcut_label = app->gui->createLabel((*it)->name.data(), 2);
		(*it)->shortcut_label->setLocalPos(pos.x, pos.y);

		pos.y += 30;
	}	

	return true;

	//TODO 4: Uncomment this to complete TODO 4
	/*pop_up = App->ui->CreateImage({ 0, 0, 220, 250 }, 100, 100, App->input_manager);*/

}

// Called before all Updates
bool ShortcutsManager::preUpdate()
{
	bool ret = true;

	//TODO 2: Set active state on true if had been pressed any key that we are assigned to any shortcut (DOWN, UP, REPEAT)
	//You must do:
	//	- Check if queues are empty
	//	- Iterate each queue
	//	- Check each queue element with our shortcuts list (check shortcut command and type)
	//	- If this checks are true turn the right shortcut active = true

	for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
	{
		vector<const char*>::iterator sc_input;
		for (sc_input = app->input->down_shortcuts.begin(); sc_input != app->input->down_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == DOWN && (*sc)->command == (*sc_input))
				(*sc)->active = true;
		}

		for (sc_input = app->input->repeat_shortcuts.begin(); sc_input != app->input->repeat_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == REPEAT && (*sc)->command == (*sc_input))
				(*sc)->active = true;
		}

		for (sc_input = app->input->up_shortcuts.begin(); sc_input != app->input->up_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == UP && (*sc)->command == (*sc_input))
				(*sc)->active = true;
		}
	}
	
	return ret;
}

bool ShortcutsManager::update(float dt)
{
	//http://stackoverflow.com/questions/17796921/how-to-handle-uppercase-keystrokes-in-sdl <----- NAIS

	bool ret = true;

	if (change_on_command)
	{
		for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
		{
			if ((*sc)->ready_to_change && new_command != NULL)
			{
				// Check repeated commands.
				(*sc)->command = new_command;
				changeShortcutCommand((*sc));
				(*sc)->ready_to_change = false;
				change_on_command = false;
				new_command = NULL;
				
			}
		}
	}	

	return ret;
}

// Called after all Updates
bool ShortcutsManager::postUpdate()
{
	bool ret = true;

	//We must turn down all activity shortcuts again to reset their state
	for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
		(*sc)->active = false;

	return ret;
}

// Called before quitting
bool ShortcutsManager::cleanUp()
{
	bool ret = true;

	shortcuts_list.clear();

	return ret;
}

void ShortcutsManager::onGui(GuiElements* gui, GUI_EVENTS event)
{
	//TODO 4: Iterate all shortcuts cheking:
	//	- UI entity we are on it's a label
	//	- Which label we are on
	//	- Left mouse button is down (use event as MOUSE_BUTTON_LEFT_DOWN)
	//Once is checked, set this shortcut to ready to change
	
	switch (event)
	{
	case(MOUSE_LCLICK_DOWN) :
		for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
		{
			(*sc)->ready_to_change = false;   // We avoid change a previous clicked command
			if ((*sc)->command_label == gui)
			{
				(*sc)->ready_to_change = true;
				change_on_command = true;
			}
		}
		break;
	}
}

void ShortcutsManager::changeShortcutCommand(ShortCut* shortcut)
{
	shortcut->command_label->setText(shortcut->command.c_str(), 2);
	shortcut->ready_to_change = true;
}