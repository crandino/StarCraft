#ifndef __GUIRESOURCES_H__
#define __GUIRESOURCES_H__

#include "GuiElements.h"
#include "GuiLabel.h"
#include "GuiImage.h"

class GuiResources : public GuiElements
{
public:
	//Constructor
	GuiResources(const char* _entity_name, const char* _mineral, const char* _gas, iPoint pos);

	~GuiResources()
	{}


	bool start();

	bool cleanUp();

	//Blit GuiMinimap
	void draw() const;

private:

	GuiLabel*    entity_name;
	GuiLabel*    mineral;
	GuiLabel*    gas;

	GuiImage*    window;
	GuiImage*    mineral_image;
	GuiImage*    gas_image;



};

#endif  //__GUIMINIMAP_H__