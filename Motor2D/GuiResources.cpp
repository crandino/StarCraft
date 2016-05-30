#include "GuiResources.h"

GuiResources::GuiResources(const char* _entity_name, const char* _mineral, const char* _gas, iPoint pos, bool draw_element)
{
	type = RESOURCES;
	entity_name = app->gui->createLabel("0", 1);
	mineral = app->gui->createLabel("0", 1);
	gas = app->gui->createLabel("0", 1);

	window = app->gui->createImage(NULL, { 440, 43, 126, 33 });
	window->setLocalPos(pos.x, pos.y);
	window->draw_element = draw_element;

	mineral_image = app->gui->createImage(NULL, { 7, 202, 15, 13 });
	mineral_image->parent = window;
	mineral_image->setLocalPos(5, 20);
	mineral_image->draw_element = draw_element;

	gas_image = app->gui->createImage(NULL, { 27, 202, 15, 13 });
	gas_image->parent = window;
	gas_image->setLocalPos(70, 20);
	gas_image->draw_element = draw_element;

	entity_name->setText(_entity_name, 1);
	entity_name->parent = window;
	entity_name->setLocalPos(5, 2);
	entity_name->draw_element = draw_element;

	mineral->setText(_mineral, 1);
	mineral->parent = window;
	mineral->setLocalPos(23, 18);
	mineral->draw_element = draw_element;

	gas->setText(_gas, 1);
	gas->parent = window;
	gas->setLocalPos(90, 18);
	gas->draw_element = draw_element;
}

GuiResources::GuiResources(const char* _entity_name, iPoint pos, bool only_info, bool draw_element)
{
	//Only shows info
	type = RESOURCES;
	entity_name = app->gui->createLabel("0", 1);

	window = app->gui->createImage(NULL, { 440, 43, 126, 33 });
	window->setLocalPos(pos.x, pos.y);
	window->draw_element = draw_element;

	entity_name->setText(_entity_name, 1);
	entity_name->parent = window;
	entity_name->setLocalPos(5, 2);
	entity_name->draw_element = draw_element;

	this->only_info = only_info;
}


void GuiResources::draw() const
{
	if (draw_element && !only_info)
	{
		entity_name->draw();
		mineral->draw();
		gas->draw();

		window->draw();
		mineral_image->draw();
		gas_image->draw();
	}
	else
	{
		entity_name->draw();
		window->draw();
	}
}

bool GuiResources::cleanUp()
{
	return true;
}