#include "FogOfWar.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "p2Log.h"

// -------------- Structure Fog Map -----------------------------------------------------------------------------

FogMap::FogMap(const int _w, const int _h)
{
	w = _w;
	h = _h;
	//Creating a new two dimensional array of tiles
	map = new uint*[h];
	if (w)
	{
		map[0] = new uint[h * w];
		for (int i = 1; i < h; ++i)
		{
			map[i] = map[0] + i * w;
		}
	}

	//Initializing them all non-visible
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			map[x][y] = maxAlpha;
		}
	}
}

FogMap::~FogMap()
{
	//Erasing the map
	if (w)
	{
		delete[] map[0];
	}
	delete[] map;
}

void FogMap::drawCircle(int _x, int _y, int radius, bool visible)
{
	//We'll check a square around the center (_x, _y) of size radius * 2 

	//We find the top left corner tile of the square
	int x = _x - radius;
	CAP(x, 1, w - 2);
	int y = _y - radius;
	CAP(y, 1, h - 2);

	//We define if we'll be making the tiles visibles or non-visibles
	uint opacityToSet = 0;
	if (visible == false)
	{
		opacityToSet = maxAlpha;
	}

	//Checking all the cells in the square with two "for"s to traverse them all
	for (; y < _y + radius; y++)
	{
		//Making sure the cell is still in the map
		if (y < h - 1)
		{
			for (; x < _x + radius && x < w - 1; x++)
			{
				if (map[x][y] != opacityToSet)
				{
					//Getting an aproximate distance from the center and comparing it to the radius to decide if it's part of the circle or not
					int distance = (x - _x)*(x - _x) + (y - _y) * (y - _y);
					if (distance < radius * radius)
					{
						map[x][y] = opacityToSet;
					}
				}
			}

		}
		//Resetting the x coordinate.  We're not reseting it in the "for" statement because we need to CAP the x values before using them.
		x = _x - radius;
		CAP(x, 1, w - 2);
	}

}

void FogMap::setAll(bool visible)
{
	//We define if we'll be making the tiles visibles or non-visibles
	uint opacityToSet = 0;
	if (visible == false)
	{
		opacityToSet = maxAlpha;
	}

	//Setting all the tiles to the correspondant value
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			map[x][y] = opacityToSet;
		}
	}
}

void FogMap::copyTo(FogMap* output)
{
	if (output == NULL)
	{
		return;
	}
	//Copying the map
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			output->map[x][y] = map[x][y];
		}
	}
}

bool FogMap::isVisible(int x, int y)
{
	//Checking the requested tile is in the map
	if (x >= 0 && x < w && y >= 0 && y < h)
	{
		//This comparison defines the amount of Alpha a tile must have to decide if it's either visible or not
		if (map[x][y] < maxAlpha / 2)
		{
			return true;
		}
	}
	return false;
}

void FogMap::softenSection(int x1, int y1, int x2, int y2, float fadeRatio)
{
	//Capping the fade to healthy values
	CAP(fadeRatio, 1.3f, 100);

	//Making sure the section requested is in the map
	CAP(x1, 1, w - 1);
	CAP(x2, x1, w - 1);

	CAP(y1, 1, w - 1);
	CAP(y2, y1, w - 1);

	/*
	We'll need to go through the requested section twice:
	- First from top right to bottom left.
	- Then from bottom left to top right.
	If we didn't do this, the sections would only soften in two directions.
	To clearly see why we're doing this, comment one of the two loops and compare the fog borders.
	*/

	//From top right to bottom left
	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			int myAlpha = map[x][y];
			if ((x + 1) < w){
				if (map[x + 1][y] > myAlpha * fadeRatio)
					myAlpha = map[x + 1][y] / fadeRatio;
			}
			if (map[x - 1][y] > myAlpha * fadeRatio)
				myAlpha = map[x - 1][y] / fadeRatio;
			if (map[x][y + 1] > myAlpha * fadeRatio)
				myAlpha = map[x][y + 1] / fadeRatio;
			if (map[x][y - 1] > myAlpha * fadeRatio)
				myAlpha = map[x][y - 1] / fadeRatio;
			map[x][y] = myAlpha;
		}
	}

	//From bottom left to top right
	for (int y = y2; y >= y1; y--)
	{
		for (int x = x2; x >= x1; x--)
		{
			int myAlpha = map[x][y];
			if ((x + 1) < w){
				if (map[x + 1][y] > myAlpha * fadeRatio)
					myAlpha = map[x + 1][y] / fadeRatio;
			}
			if (map[x - 1][y] > myAlpha * fadeRatio)
				myAlpha = map[x - 1][y] / fadeRatio;
			if (map[x][y + 1] > myAlpha * fadeRatio)
				myAlpha = map[x][y + 1] / fadeRatio;
			if (map[x][y - 1] > myAlpha * fadeRatio)
				myAlpha = map[x][y - 1] / fadeRatio;
			map[x][y] = myAlpha;
		}
	}

}

// -------------- Module Fog of War -----------------------------------------------------------------------------

FogOfWar::FogOfWar(bool enabled) : Module(enabled)
{
	name.assign("fog_of_war");
}

// Destructor
FogOfWar::~FogOfWar()
{}


bool FogOfWar::cleanUp()
{
	eraseMaps();
	return true;
}

bool FogOfWar::setUp(uint graphicalW, uint graphicalH, uint _tileW, uint _tileH, uint nMaps)
{
	//If there are maps loaded already, unload them
	if (ready)
	{
		eraseMaps();
	}

	//Create as many maps as necessary
	for (uint n = 0; n < nMaps; n++)
		createMap(graphicalW / _tileW, graphicalH / _tileH);

	//Save the width and height of each tile
	tileW = _tileW;
	tileH = _tileH;
	
	ready = true;
	return true;
}

void FogOfWar::eraseMaps()
{
	//Release all created maps
	for (int n = 0; n < maps.size(); n++)
	{
		RELEASE(maps[n]);
	}
	maps.clear();
	ready = false;
}

void FogOfWar::draw()
{
	//Cheking if the module has been SetUp
	if (ready == false)
		return;

	//Rect to draw, we'll only draw the tiles displayed on screen (culling)
	int startX = -app->render->camera.x / tileW;
	int startY = -app->render->camera.y / tileH;

	int hud_terran_height = 100;   // Pixels height of Terran HUD
	int endX = ((app->render->camera.w - app->render->camera.x) / tileW ) + 1;
	int endY = (((app->render->camera.h - hud_terran_height) - app->render->camera.y) / tileH )+ 1;

	int max_map_height = maps.front()->getHeight();
	int max_map_width = maps.front()->getWidth();

	SDL_Rect r = { 0, 0, tileW, tileH };

	//Next function enables the blending of the texture
	//SDL_SetTextureBlendMode(fow, SDL_BLENDMODE_BLEND);

	//Drawing all fog maps
	for (vector<FogMap*>::reverse_iterator currentMap = maps.rbegin(); currentMap != maps.rend(); ++currentMap)
	{
		if ((*currentMap)->draw)
		{
			//Soften the fog edges of the section we'll render
			(*currentMap)->softenSection(startX, startY, endX, endY);
			for (int y = startY; y <= endY && y < max_map_height; ++y)
			{
				for (int x = startX; x <= endX && x < max_map_width; ++x)
				{
					//Now the fog is just black rectangles with diferents alphas. Diferent methods will be explained.
					//This other, changes its alpha
					SDL_SetTextureAlphaMod(fow, (*currentMap)->map[x][y]);

					//Finally, blit can run correctly with the suitable alpha texture
					app->render->blit(fow, x * tileW, y * tileH, &r);

					/*
					Another option would be:
					App->render->AddRect({ x * tileW, y * tileH, tileW, tileH }, true, 0, 0, 0, (*currentMap)->map[x][y]);
					*/
				}
			}
		}
	}
}

void FogOfWar::drawCircle(int x, int y, uint radius, bool visible, int map)
{
	//Cheking if the module has been SetUp
	if (ready == false)
		return;

	//Transforming the recieved data from pixels to Tiles
	int tileX = floor(x / tileW);
	int tileY = floor(y / tileH);
	int tileRadius = floor(radius / ((tileW + tileH) / 2));

	if (map >= 0)
	{
		//Drawing the circle on a single map
		if (map < maps.size())
		{
			maps[map]->drawCircle(tileX, tileY, tileRadius, visible);
		}
	}
	else
	{
		//Drawing the circle on all the maps
		for (int n = 0; n < maps.size(); n++)
		{
			maps[n]->drawCircle(tileX, tileY, tileRadius, visible);
		}
	}
}

void FogOfWar::clearMap(int map)
{
	//Cheking if the module has been SetUp
	if (ready == false)
		return;

	if (map >= 0)
	{
		//Clearing a single map
		if (map < maps.size())
		{
			maps[map]->setAll(false);
		}
	}
	else
	{
		//Clearing all maps
		for (int n = 0; n < maps.size(); n++)
		{
			maps[n]->setAll(false);
		}
	}
}

bool FogOfWar::copy(uint from, uint to)
{
	if (ready && (from >= 0 && from < maps.size()) && (to >= 0 && to < maps.size()))
	{
		return false;
	}
	maps[from]->copyTo(maps[to]);
	return true;
}

bool FogOfWar::isVisible(int x, int y)
{
	//Cheking if the module has been SetUp
	if (ready == false)
		return false;

	//Transforming input data from pixels to tiles
	bool ret = true;
	int tileX = floor(x / tileW);
	int tileY = floor(y / tileH);
	//We'll check all maps visibility. This code may change
	for (int n = 0; n < maps.size() && ret; n++)
	{
		if (maps[n]->isVisible(tileX, tileY) == false)
		{
			ret = false;
		}
	}
	return ret;
}

int FogOfWar::createMap(int w, int h, int maxAlpha)
{
	FogMap* tmp = NULL;
	fow = app->tex->loadTexture("maps/FogOfWar.png");
	//Next function enables the blending of the texture
	SDL_SetTextureBlendMode(fow, SDL_BLENDMODE_BLEND);

	tmp = new FogMap(w, h);
	if (tmp)
	{
		tmp->maxAlpha = maxAlpha;
		maps.push_back(tmp);
	}
	return maps.size();
}