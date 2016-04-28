#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"
#include "Timer.h"
#include "Point2d.h"
#include "Collision.h"
#include "Gui.h"
#include "PugiXml\src\pugixml.hpp"

//Number to change the number of waves
#define TOTALWAVES 2
#define WAVETIME1 1.0f //120 = 2 minutes per wave in the future or some other game designish number
#define WAVETIME2 1.0f
#define	SIZE1X 1 // Changes number of zerglings per wave
#define SIZE1Y 1
#define	SIZE2X 10 // Changes number of zerglings per wave
#define SIZE2Y 1
#define	SIZE3X 5 // Changes number of zerglings per wave
#define SIZE3Y 2
#define TOTALUNITSALLWAVES (SIZE1X*SIZE1Y + SIZE2X*SIZE2Y + SIZE3X*SIZE2Y)
#define ZERGLINGSCORE 20
#define COMMANDCENTERPOSITION {1500, 2250}
#define SIZEMARINESX 2
#define SIZEMARINESY 2

class GuiImage;
using namespace std;

//XML information
struct SizeWave
{
	uint zergling_quantity;
	uint hydralisk_quantity;
	uint mutalisk_quantity;
	/*Rest of units*/
};

struct initialSizePlayer
{
	uint marines_quantity;
	uint medic_quantity;
	uint scv_quantity;
};

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
	bool game_over = false;
	iPoint initial_position;

	/*---- Wave Creation ----*/
	int center;
	int radius_spawn_offset = 30;
	uint total_kills_game = 0;
	uint total_units_killed_currentFrame = 0;

	//-------------Resources------------------
	int       mineral_resources = 1000;
	int       gas_resources = 1000;
	int       resources = 0;

public:

	GameManager()
	{
		name.assign("game_manager");
	}

	void displayVictoryScreen();

	void displayDefeatScreen();

	bool checkGameOver();

	bool victory = false;

	bool awake(pugi::xml_node &node);

	void startGame();

	void restartGame();

	bool quitGame();

	void addPoints(uint points);

	bool start();

	bool preUpdate();

	bool update(float dt);
	
	bool postUpdate();

	bool cleanUp();

	void onGui(GuiElements* ui, GUI_EVENTS event);

	void createMarines(iPoint position,unsigned int sizex, unsigned int sizey);

	void eraseEnemiesIfKilled();

	void AddPointsEnemy(Entity* e);

public:
	//Time Management attributes
	Timer general_time;
	Timer time_between_waves;
	Timer random_generator;
	Timer ending_game;
	Timer winning_game;
	Timer optimizationEraseEnemy;


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
	bool is_victory_screen_on = false;

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

	//commandCenterDestroyed
	bool command_center_destroyed = false;
	//Sound
	unsigned int fx_click;
	bool isGameStarted() const;
	
	//Wave Control
	bool wave_wiped = false;

//Utils
	int sizeWave();

//XML loaded info -------
	SizeWave wave1;
	SizeWave wave2;

	initialSizePlayer initial_size;

	uint zergling_score;
	uint hydralisk_score;
	uint mutalisk_score;

//XML loaded info end -------
private:
	uint previous_unit_killed = 0;

	bool start_game = false;
	
	unsigned int size_marines_x = SIZEMARINESX;
	unsigned int size_marines_y = SIZEMARINESY;
};

#endif