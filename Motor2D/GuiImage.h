#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "GuiElements.h"

class GuiImage : public GuiElements
{
public:

	GuiImage(const SDL_Texture* texture);
	GuiImage(const SDL_Texture* texture, const SDL_Rect& section);
	GuiImage(GuiImage* image, iPoint position);
	~GuiImage();

	void setSection(const SDL_Rect& section);
	void draw() const;
	void draw_static() const;

private:

	SDL_Rect section;
	const SDL_Texture* texture = nullptr;

};

#endif __GUIIMAGE_H__


