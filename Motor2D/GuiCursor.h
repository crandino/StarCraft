#ifndef __GUICURSOR_H__
#define __GUICURSOR_H__

#include "GuiElements.h"

class GuiCursor : public GuiElements
{
public:

	GuiCursor(const SDL_Texture* texture);
	~GuiCursor();

	void update();
	void draw() const;
	void debugDraw() const;

	const SDL_Texture* texture = nullptr;
	Animation* current_animation;
	Animation  idle;
	Animation  selection_anim;
	Animation  left_disp;
	Animation  right_disp;
	Animation  up_disp;
	Animation  down_disp;
};


#endif !__GUICURSOR_H__