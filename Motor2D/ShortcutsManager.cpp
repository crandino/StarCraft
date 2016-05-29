#include "ShortcutsManager.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiImage.h"
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

	// Resolvers:
	action_resolver.insert(pair<string, ACTIONS>("FOCUS_ATTACK", FOCUS_ATTACK));
	action_resolver.insert(pair<string, ACTIONS>("LOCATE_JIM_RAYNOR", LOCATE_JIM_RAYNOR));
	action_resolver.insert(pair<string, ACTIONS>("LOCATE_COMMAND_CENTER", LOCATE_COMMAND_CENTER));
	action_resolver.insert(pair<string, ACTIONS>("LOCATE_LAST_ATTACK_POSITION", LOCATE_LAST_ATTACK_POSITION));
	action_resolver.insert(pair<string, ACTIONS>("SAVE_GAME", SAVE_GAME));
	action_resolver.insert(pair<string, ACTIONS>("LOAD_GAME", LOAD_GAME));

	input_type_resolver.insert(pair<string, INPUT_TYPE>("DOWN", DOWN));
	input_type_resolver.insert(pair<string, INPUT_TYPE>("UP", UP));
	input_type_resolver.insert(pair<string, INPUT_TYPE>("REPEAT", REPEAT));

	//Loading shortcuts path xml
	for (node = node.child("shortcut"); node && ret; node = node.next_sibling("shortcut"))
	{
		ShortCut* shortcut = new ShortCut();
		shortcut->type = input_type_resolver.at(node.attribute("type").as_string());
		shortcut->action = action_resolver.at(node.attribute("action").as_string());
		
		shortcut->name = node.attribute("name_action").as_string();
		shortcut->command = node.attribute("key_associated").as_string();

		key_to_action.insert(pair<string, ACTIONS>(shortcut->command, shortcut->action));

		shortcut->active = false;
		shortcuts_list.push_back(shortcut);
	}

	return ret;
}

// Call before first frame
bool ShortcutsManager::start()
{
	// Now, render is loaded.
	iPoint pos = { 20, 20 };
	for (list<ShortCut*>::iterator it = shortcuts_list.begin(); it != shortcuts_list.end(); ++it)
	{
		(*it)->shortcut_label = app->gui->createLabel((*it)->name.data(), 2);
		(*it)->shortcut_label->parent = app->gui->controls_panel;
		(*it)->shortcut_label->setLocalPos(pos.x, pos.y);
		(*it)->shortcut_label->disable_element();

		(*it)->command_label = app->gui->createLabel((*it)->command.data(), 2);
		(*it)->command_label->parent = app->gui->controls_panel;
		(*it)->command_label->setLocalPos(pos.x + 200, pos.y);
		(*it)->command_label->disable_element();
		(*it)->command_label->setListener(this);

		pos.y += 20;
	}	

	return true;
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
		vector<ACTIONS>::iterator sc_input;
		for (sc_input = app->input->down_shortcuts.begin(); sc_input != app->input->down_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == DOWN && (*sc)->action == *sc_input)
				(*sc)->active = true;
		}

		for (sc_input = app->input->repeat_shortcuts.begin(); sc_input != app->input->repeat_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == REPEAT && (*sc)->action == *sc_input)
				(*sc)->active = true;
		}

		for (sc_input = app->input->up_shortcuts.begin(); sc_input != app->input->up_shortcuts.end(); ++sc_input)
		{
			if ((*sc)->type == UP && (*sc)->action == *sc_input)
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
				// Check repeated commands? Not done!
				ACTIONS act = (*sc)->action;
				key_to_action.erase((*sc)->command);

				(*sc)->command = new_command;
				changeShortcutCommand((*sc));

				key_to_action.insert(pair<string, ACTIONS>((*sc)->command, act));

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
	shortcut->ready_to_change = false;
}

bool ShortcutsManager::isCommandActive(ACTIONS action)
{
	for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
	{
		if ((*sc)->active && (*sc)->action == action)
			return true;
	}
		
	return false;
}

void ShortcutsManager::showShortcuts()
{
	for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
	{
		(*sc)->command_label->enable_element();
		(*sc)->shortcut_label->enable_element();
	}
}

void ShortcutsManager::hideShortcuts()
{
	for (list<ShortCut*>::iterator sc = shortcuts_list.begin(); sc != shortcuts_list.end(); ++sc)
	{
		(*sc)->command_label->disable_element();
		(*sc)->shortcut_label->disable_element();
	}
}