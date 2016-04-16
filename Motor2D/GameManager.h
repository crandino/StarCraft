#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"
#include "Timer.h"
#include "Point2d.h"
#include "Collision.h"
#include "Gui.h"

class GuiImage;
using namespace std;

//Class that manages the game. The win lose cycle, the points earned, the resources, waves etc..

/*
Place a timer, entity manager communicate zerg list/map etc..
*/
class GameManager : public Module
{
public:
	int current_waves = 0;
	int total_waves = 2;
	int score = 0;
	int enemy_count = 0;
	uint kill_count = 0;
	bool is_finished = false;
	bool game_over = false;
	iPoint initial_position;


	/*---- Wave Creation ----*/
	int center;
	int radius_spawn_offset = 30;
	uint total_kills_game = 0;
	uint total_units_killed_currentFrame = 0;


public:

	GameManager()
	{
		name.assign("GameManager");
	}


	bool victory = false;

	void startGame();

	bool quitGame();

	void addPoints(uint points);

	bool start();

	bool update(float dt);
	
	bool postUpdate();

	bool cleanUp();

	void onGui(GuiElements* ui, GUI_EVENTS event);

public:
	//Time Management attributes
	Timer general_time;
	Timer time_between_waves;
	Timer random_generator;

	//Score system attributes
	uint score_current_wave = 0;
	uint total_score = 0;

	//Start/Exit Button
	SDL_Texture* start_image = nullptr;

	GuiImage* title_screen = nullptr;
	GuiImage* start_button = nullptr;
	GuiImage* exit_button = nullptr;


private:
	uint previous_unit_killed = 0;

	bool start_game = false;
};

#endif