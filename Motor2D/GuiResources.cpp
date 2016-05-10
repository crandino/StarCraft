#include "GuiResources.h"

GuiResources::GuiResources(const char* _entity_name,const char* _mineral, const char* _gas, iPoint pos)
{
	type = RESOURCES;
	entity_name = app->gui->createLabel("0", 2);
	mineral = app->gui->createLabel("0", 2);
	gas = app->gui->createLabel("0", 2);

	window = app->gui->createImage(NULL, { 440, 43, 126, 33 });
	window->setLocalPos(pos.x, pos.y);
	mineral_image = app->gui->createImage(NULL, { 7, 202, 15, 13 });
	mineral_image->parent = window;
	mineral_image->setLocalPos(5, 20);
	gas_image = app->gui->createImage(NULL, { 27, 202, 15, 13 });
	gas_image->parent = window;
	gas_image->setLocalPos(100, 20);

	char n[20];
	sprintf_s(n, 20, _entity_name);
	entity_name->setText(_entity_name, 2);
	entity_name->parent = window;
	entity_name->setLocalPos(5, 5);

	char n1[20];
	sprintf_s(n1, 20, _mineral);
	mineral->setText(_mineral, 2);
	mineral->parent = window;
	mineral->setLocalPos(8, 20);

	char n2[20];
	sprintf_s(n2, 20, _gas);
	gas->setText(_gas, 2);
	gas->parent = window;
	gas->setLocalPos(103, 20);
}


void GuiResources::draw() const
{
	entity_name->draw();
	mineral->draw();
	gas->draw();

	window->draw();
	mineral_image->draw();
	gas_image->draw();
}

bool GuiResources::cleanUp()
{
	return true;
}