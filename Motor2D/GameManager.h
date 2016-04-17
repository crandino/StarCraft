#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"
#include "Timer.h"
#include "Point2d.h"
#include "Collision.h"
#include "Gui.h"

//Number to change the number of waves
#define TOTALWAVES 2
#define WAVETIME1 5.0f //120 = 2 minutes per wave in the future or some other game designish number
#define WAVETIME2 15.0f
#define	SIZE1 3 // Changes number of zerglings per wave
#define	SIZE2 5 // Changes number of zerglings per wave
#define	SIZE3 10 // Changes number of zerglings per wave
#define TOTALUNITSALLWAVES (SIZE1 + SIZE2 + SIZE3)
#define ZERGLINGSCORE 20
#define COMMANDCENTERPOSITION {1500, 2250}
#define ENDINGTIME 5.0f
#define VICTORYTIME 5.0f

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

	uint marineCounterDeath = 0;

public:

	GameManager()
	{
		name.assign("GameManager");
	}

	void displayVictoryScreen();

	void displayDefeatScreen();

	bool checkGameOver();

	bool victory = false;

	void startGame();

	void restartGame();

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
	Timer ending_game;
	Timer winning_game;

	//Score system attributes
	uint score_current_wave = 0;
	uint total_score = 0;

	//Start/Exit Button
	SDL_Texture* start_image = nullptr;

	GuiImage* title_screen = nullptr;
	GuiImage* start_button = nullptr;
	GuiImage* exit_button = nullptr;
	

	//Victory Screen
	SDL_Texture* victory_img = nullptr;
	GuiImage* victory_screen = nullptr;

	bool won = false;

	//Defeat Screen
	GuiImage* defeat_screen = nullptr;
	SDL_Texture* defeat_img = nullptr;
	bool is_defeat_screen_on = false;

	//Ending Buttons
	GuiImage* retry_button = nullptr;
	GuiImage* close_button = nullptr;

	//close bool
	bool close = false;


	//Sound
	unsigned int fx_click;

private:
	uint previous_unit_killed = 0;

	bool start_game = false;
	
};

#endif