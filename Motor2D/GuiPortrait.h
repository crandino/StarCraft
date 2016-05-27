#ifndef __GUIPORTRAIT_H__
#define __GUIPORTRAIT_H__

#include "GuiElements.h"

class SDL_Texture;
class Animation;

class GuiPortrait : public GuiElements
{
public:

	GuiPortrait(const SDL_Texture* texture, Animation anim);
	~GuiPortrait();

	void setSection(const SDL_Rect& section);
	void draw() const;
	void draw_static() const;

private:

	Animation anim;
	SDL_Rect section;
	const SDL_Texture* texture = nullptr;
	
public:

	Animation* current_animation;

};

#endif __GUIPORTRAIT_H__