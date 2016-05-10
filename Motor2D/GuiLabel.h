#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "GuiElements.h"
#include <string>

struct _TTF_Font;
struct SDL_Texture;

class GuiLabel : public GuiElements
{
public:

	GuiLabel(const char* text, int kind_of_font);	
	~GuiLabel();

	void setText(const char* text, int font, uint max_wrapping = 680);
	const SDL_Texture* getTexture() const;
	void draw() const;


private:

	SDL_Texture* texture = nullptr;
};


#endif __GUILABEL_H__
