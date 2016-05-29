#include "ShortcutsManager.h"
#include "Gui.h"
#include "GuiLabel.h"

ShortcutsManager::ShortcutsManager(bool enabled) : Module(enabled)
{
	name.append("shortcuts_manager");
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
/*	iPoint pos = { 0, 0 };
	for (list<ShortCut*>::iterator it = shortcuts_list.begin(); it != shortcuts_list.end(); ++it)
	{
		(*it)->command_label = app->gui->createLabel((*it)->command.data(), 2);
		(*it)->command_label->setLocalPos(pos.x, pos.y);
		(*it)->shortcut_label = app->gui->createLabel((*it)->name.data(), 2);
		(*it)->shortcut_label->setLocalPos(pos.x += 20, pos.y += 20);
	}*/	

	return true;

	//TODO 4: Uncomment this to complete TODO 4
	/*pop_up = App->ui->CreateImage({ 0, 0, 220, 250 }, 100, 100, App->input_manager);
*/
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

	//DOWN
	//Code with down queues here
	//if (!App->input->down_queue.empty())
	//{
	//	for (int i = 0; i < App->input->down_queue.size(); i++)
	//	{
	//		list<ShortCut*>::iterator it = shortcuts_list.begin();
	//		while (it != shortcuts_list.end())
	//		{
	//			if (App->input->down_queue.front() + i == (*it)->command && (*it)->type == DOWN)
	//				(*it)->active = true;
	//			++it;
	//		}
	//	}
	//}

	////UP
	////Code with up queues here
	//if (!App->input->up_queue.empty())
	//{
	//	for (int i = 0; i < App->input->up_queue.size(); i++)
	//	{
	//		list<ShortCut*>::iterator it = shortcuts_list.begin();
	//		while (it != shortcuts_list.end())
	//		{
	//			if (App->input->up_queue.front() + i == (*it)->command && (*it)->type == UP)
	//				(*it)->active = true;
	//			++it;
	//		}
	//	}
	//}

	////REPEAT
	////Code with repeat queues here
	//if (!App->input->repeat_queue.empty())
	//{
	//	for (int i = 0; i < App->input->repeat_queue.size(); i++)
	//	{
	//		list<ShortCut*>::iterator it = shortcuts_list.begin();
	//		while (it != shortcuts_list.end())
	//		{
	//			if (App->input->repeat_queue.front() + i == (*it)->command && (*it)->type == REPEAT)
	//				(*it)->active = true;
	//			++it;
	//		}
	//	}
	//}

	return ret;
}

bool ShortcutsManager::update(float dt)
{
	//http://stackoverflow.com/questions/17796921/how-to-handle-uppercase-keystrokes-in-sdl <----- NAIS

	bool ret = true;

	//list<ShortCut*>::iterator it = shortcuts_list.begin();
	//while (it != shortcuts_list.end())
	//{
	//	if ((*it)->ready_to_change)
	//	{
	//		static SDL_Event event;

	//		SDL_WaitEvent(&event);

	//		if (event.type == SDL_KEYDOWN)
	//		{
	//			//NO ES COMPROBA SI M'ÉS D'UN SHORTCUT TENEN EL MATEIX COMMAND!!
	//			(*it)->command = SDL_GetScancodeName(event.key.keysym.scancode);
	//			ChangeShortcutCommand((*it));
	//			(*it)->ready_to_change = false;
	//		}
	//	}

	//	++it;
	//}

	return ret;
}

// Called after all Updates
bool ShortcutsManager::postUpdate()
{
	bool ret = true;

	//TODO 2: We must turn down all activity shortcuts again to reset their state
	list<ShortCut*>::iterator it = shortcuts_list.begin();

	while (it != shortcuts_list.end())
	{
		if ((*it)->active)
			(*it)->active = false;

		++it;
	}

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
	/*if (gui->type == LABEL)
	{
		list<ShortCut*>::iterator it = shortcuts_list.begin();

		while (it != shortcuts_list.end())
		{
			if (gui == (*it)->command_label && event == MOUSE_BUTTON_LEFT_DOWN)
			{
				(*it)->ready_to_change = true;
			}
			++it;
		}

	}*/
}

void ShortcutsManager::changeShortcutCommand(ShortCut* shortcut)
{
	/*char n[20];
	sprintf_s(n, 20, "%c", shortcut->command);
	shortcut->command_label->SetText(n);

	shortcut->ready_to_change = true;*/
}