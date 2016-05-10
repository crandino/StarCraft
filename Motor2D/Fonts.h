#ifndef __FONTS_H__
#define __FONTS_H__

#include "Module.h"
#include <list>
#include "SDL\include\SDL_pixels.h"

#define DEFAULT_FONT "Starcraft_font.ttf"
#define DEFAULT_FONT_SIZE 20

struct SDL_Texture;
struct _TTF_Font;

class Fonts : public Module
{
public:

	Fonts();

	// Destructor
	virtual ~Fonts();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before quitting
	bool cleanUp();

	// Load Font
	_TTF_Font* const load(const char* path, int size = 12);

	// Create a surface from text
	SDL_Texture* print(const char* text, SDL_Color color, int kind_of_font, uint max_wrapping, _TTF_Font* font = NULL);

	bool calcSize(const char* text, int& width, int& height, _TTF_Font* font = NULL) const;

public:

	list<_TTF_Font*>	fonts;
	_TTF_Font*			default;
	_TTF_Font*			default_2;
};


#endif // __FONTS_H__