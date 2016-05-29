#ifndef __GUIRESOURCES_H__
#define __GUIRESOURCES_H__

#include "GuiElements.h"
#include "GuiLabel.h"
#include "GuiImage.h"

class GuiResources : public GuiElements
{
public:
	//Constructor
	GuiResources(const char* _entity_name, const char* _mineral, const char* _gas, iPoint pos, bool draw_element = false);
	GuiResources(const char* _entity_name, iPoint pos, bool only_info, bool draw_element = false);

	~GuiResources()
	{}
	
	bool start();

	bool cleanUp();

	//Blit GuiMinimap
	void draw() const;

private:

	GuiLabel*    entity_name = nullptr;
	GuiLabel*    mineral = nullptr;
	GuiLabel*    gas = nullptr;

	GuiImage*    window = nullptr;
	GuiImage*    mineral_image = nullptr;
	GuiImage*    gas_image = nullptr;

	bool only_info = false;

};

#endif  //__GUIRESOURCES_H__