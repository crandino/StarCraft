#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Textures.h"
#include "FileSystem.h"
#include "Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "Motor2D/SDL_ttf/libx86/SDL2_ttf.lib")

Fonts::Fonts() : Module()
{
	name.assign("fonts");
}

// Destructor
Fonts::~Fonts()
{}

// Called before render is available
bool Fonts::awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");
	bool ret = true;

	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	else
	{
		const char* path = conf.child("default_font").attribute("file").as_string(DEFAULT_FONT);
		int size = conf.child("default_font").attribute("size").as_int(DEFAULT_FONT_SIZE);
		default = load(path, size);

		pugi::xml_node		node = conf.child("default_font");
		node = node.next_sibling("default_font");

		const char* path2 = node.attribute("file").as_string(DEFAULT_FONT);
		int size2 = node.attribute("size").as_int(DEFAULT_FONT_SIZE);
		default_2 = load(path2, size2);

	}

	return ret;
}

// Called before quitting
bool Fonts::cleanUp()
{
	if(!active)
		return true;

	LOG("Freeing True Type fonts and library");

	list<TTF_Font*>::iterator i = fonts.begin();

	while (i != fonts.end())
	{
		TTF_CloseFont((*i));
		++i;
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
TTF_Font* const Fonts::load(const char* path, int size)
{
	TTF_Font* font = TTF_OpenFontRW(app->fs->load(path), 1, size);

	if (font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
	}
	else
	{
		LOG("Successfully loaded font %s size %d", path, size);
		fonts.push_back(font);
	}

	return font;
}

// Print text using font
SDL_Texture* Fonts::print(const char* text, SDL_Color color, int kind_of_font, uint max_wrapping, TTF_Font* font)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface;

	if (kind_of_font == 1)
		surface = TTF_RenderText_Blended_Wrapped(default, text, color, max_wrapping);
	else
		surface = TTF_RenderText_Blended_Wrapped(default_2, text, color, max_wrapping);

	if (surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = app->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

// calculate size of a text
bool Fonts::calcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	bool ret = false;

	if (!active)
		return false;

	if (TTF_SizeText((font) ? font : default, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}