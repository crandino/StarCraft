#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "GuiElements.h"
#include <string>

struct _TTF_Font;
struct SDL_Texture;

class GuiLabel : public GuiElements
{
public:

	GuiLabel();

	GuiLabel(const char* txt, const int x, const int y);

	// Destructor
	virtual ~GuiLabel();

	bool update(float dt);

	void print(string _text, bool isPassword = false);

	// Called before quitting
	bool cleanUp();

	string getText(bool get_password = false) const;

private:

	string	text;
	string	password;

public:

	SDL_Texture* texture;

};

#endif __GUILABEL_H__
