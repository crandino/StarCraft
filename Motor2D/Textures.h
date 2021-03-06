#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Module.h"
#include <list>

struct SDL_Texture;
struct SDL_Surface;

using namespace std;

class Textures : public Module
{
public:

	Textures(bool enabled);

	// Destructor
	~Textures();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before the first frame
	bool start();

	// Called before quitting
	bool cleanUp();

	// Load Texture
	SDL_Texture* const	loadTexture(const char* path);
	bool				unloadTexture(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface);
	void				GetSize(const SDL_Texture* texture, unsigned int& width, unsigned int& height) const;

public:

	list<SDL_Texture*>	textures;
};


#endif // __TEXTURES_H__
