#ifndef __FOGOFWAR_H__
#define __FOGOFWAR_H__

#include "Module.h"
#include "SDL\include\SDL_render.h"
#include "p2Defs.h"
#include <vector>

using namespace std;

class FogMap
{
public:
	FogMap(int width, int height);
	~FogMap();

	//Draw a circle onto the map
	void drawCircle(int _x, int _y, int radius, bool visible = true);

	//Set all tiles to a value
	void setAll(bool visible);

	//Copy this map's tiles to another map
	void copyTo(FogMap* output);

	//Returns if a certain tile is visible or not
	bool isVisible(int x, int y);

	//Number of width tiles
	uint getWidth() { return w; }
	//Number of height tiles
	uint getHeight() { return h; }

	//Soften the edges of a certain section of the map
	void softenSection(int x1, int y1, int x2, int y2, float fadeRatio = 1.5f);

	//Alpha the non-visible tiles will have
	uint maxAlpha = 255;

	uint** map;

	//Defines if this map will be drawn
	bool draw = true;

private:
	uint w = 0;
	uint h = 0;
};

class FogOfWar : public Module
{
public:

	FogOfWar();

	// Destructor
	~FogOfWar();

	bool cleanUp();

	//Create & Initialize the fog maps
	bool setUp(uint graphicalW, uint graphicalH, uint tileW = 32, uint tileH = 32, uint nMaps = 1);
	//Delete the fog maps
	void eraseMaps();

	//Draw the fog
	void draw();

	//Draw a circle on a certain Fog Map. Leave on -1 to draw on all
	void drawCircle(int x, int y, uint radius, bool visible = true, int map = -1);
	//Reset a Fog Map to not visible. Leave on -1 to reset all.
	void clearMap(int map = -1);
	//Copy a certain Fog map tiles values to another.
	bool copy(uint from, uint to);

	//Return if a certain tile is visible or not
	bool isVisible(int x, int y);

private:
	//Create a new FogMap
	int createMap(int w, int h, int maxAlpha = 255);

public:
	//List of Fog maps
	vector<FogMap*> maps;

private:
	//Declares if the module has been SetUp and it's usable or not.
	bool ready = false;
	//Width & Height of each tile in pixels
	int tileW, tileH = 0;

	//Fog of war's texture
	SDL_Texture* fow;
};

#endif //!__FOGOFWAR_H__