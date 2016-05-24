#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"
#include "Timer.h"
#include "Point2d.h"
#include "Collision.h"
#include "Gui.h"
#include "PugiXml\src\pugixml.hpp"

class GuiTimer;

//Number to change the number of waves
#define TOTALWAVES 2
#define WAVETIME1 5.0f //120 = 2 minutes per wave in the future or some other game designish number
#define WAVETIME2 1.0f
#define	SIZE1X 1 // Changes number of zerglings per wave
#define SIZE1Y 1
#define	SIZE2X 10 // Changes number of zerglings per wave
#define SIZE2Y 1
#define	SIZE3X 5 // Changes number of zerglings per wave
#define SIZE3Y 2
#define TOTALUNITSALLWAVES (SIZE1X*SIZE1Y + SIZE2X*SIZE2Y + SIZE3X*SIZE2Y)
#define SIZEMARINESX 2
#define SIZEMARINESY 2


enum GAME_STATE
{
	INITIAL_SCREEN,
	PREPARATION,
	FIRST_PHASE,
	BOMB_LANDING,
	SECOND_PHASE,
	BOMB_ACTIVATION,
	FINAL_PHASE,

	WIN,
	HOLD,
	LOSE,
	QUIT
};

enum WAVE_STATE
{
	WAITING_FOR_WAVE_TO_START,
	BEGINNING_WAVE,
	MIDDLE_WAVE,
	END_WAVE
};

struct bombPosition
{
	iPoint north_west = { 300, 630 };
	iPoint north_east = { 2450, 120 };
	iPoint south_west = { 2000, 3850 };
	iPoint south_east = { 3560, 3825 };
};

using namespace std;

//  -------- XML information ------------
struct GameInformation
{
	uint total_waves;
	
	//Time
	float time_before_game_starts;
	float time_before_waves_phase1;
	float time_before_waves_phase2;
	float time_before_waves_phase3;
	float time_while_bomb_landing;
	float time_before_start;
	float time_before_end;
	float time_bomb_detonation;
};


struct SizeWave
{
	SizeWave(uint zergling, uint hydra, uint muta, uint ultra)
	{
		zergling_quantity = zergling;
		hydralisk_quantity = hydra;
		mutalisk_quantity = muta;
		ultralisk_quantity = ultra;
	}

	uint zergling_quantity;
	uint hydralisk_quantity;
	uint mutalisk_quantity;
	uint ultralisk_quantity;
	/*Rest of units*/
};

struct initialSizePlayer
{
	uint marines_quantityX;
	uint marines_quantityY;
	uint medic_quantity;
	uint scv_quantity;
};
//  -------- XML information ------------


//Class that manages the game. The win lose cycle, the points earned, the resources, waves etc...
class GameManager : public Module
{
private:
	//Debug-----
	bool	  debug = false;

public:

	GameManager(bool enabled);

	bool awake(pugi::xml_node &node);

	void addPoints(uint points);

	bool start();

	bool preUpdate();

	bool update(float dt);
	
	bool postUpdate();

	bool cleanUp();

	void onGui(GuiElements* ui, GUI_EVENTS event);

	// Saving and loading game
	bool load(pugi::xml_node &node);
	bool save(pugi::xml_node &node) const;
	vector<uint> list_ids_enemies;

	// Setting, resetting or getting game conditions
	void startGame();
	void stopGame();
	void initiateGame();
	void restartGame();
	bool isGameStarted() const;

	// Gui Victory and Defeat Screens
	void displayVictoryScreen();
	void displayDefeatScreen();

	void createMarines(iPoint position,unsigned int sizex, unsigned int sizey);
	void eraseEnemiesIfKilled();

	void AddPointsEnemy(Entity* e);

public:
	
	//-------------Resources------------------
	int  mineral_resources;
	int  gas_resources;

	void updateResources(int mineral, int gas);

	//Lose Conditions
	bool command_center_destroyed = false;
	bool jim_raynor_dead = false;

	//Find Jim
	Entity*				 jim_raynor = NULL;

	//Sound
	unsigned int fx_click;
	unsigned int fx_win;
	unsigned int fx_lose;
	unsigned int fx_wave_incoming;
	
	//Wave Control
	bool isWaveClear();

	//XML loaded info -------	
	initialSizePlayer initial_size;

	uint zergling_score;
	uint hydralisk_score;
	uint mutalisk_score;
	uint ultralisk_score;

	GameInformation gameInfo;

	uint num_zergling;
	uint num_hydralisk;
	uint num_mutalisk;
	uint num_ultralisk;

	uint original_zergling_num;
	uint original_hydra_num;
	uint original_muta_num;
	uint original_ultra_num;

	//Multipliers
	uint multiplier_hydra;
	uint multiplier_muta;
	uint multiplier_ultra;

	//Power
	uint power_hydra;
	uint power_muta;
	uint power_ultra;

	//States
	GAME_STATE			 game_state;
	WAVE_STATE			 wave_state;

	vector<SizeWave*>	 waves_info;
	vector<SizeWave*>    waves2_info;
	vector<SizeWave*>	 waves3_info;

	map<uint, Entity*>	 current_wave_entities;

	iPoint				 command_center_position;
	iPoint				 factory_position;
	iPoint				 barrack_position;
	Bomb*				 bomb;

private:

	uint				 current_wave;
	uint				 wave2_power_counter = 0;
	uint				 wave3_power_counter = 0;

	//Time Management attributes
	Timer				 timer_between_waves;
	Timer				 timer_between_game_states;

	bool				 start_game = false;
	bool				 final_music = false;


	unsigned int		 size_marines_x = SIZEMARINESX;
	unsigned int		 size_marines_y = SIZEMARINESY;

	// Check the conditions to finish the game
	void				checkingGameConditions();
	iPoint				positionRandomizerWave(int random, iPoint wave_pos);
	iPoint				positionRandomizerBomb(int random, iPoint bomb_pos);
	void				createEnemiesBombPhase();
	// Creating waves
	void			    createWave(SizeWave* size, iPoint position);
	void				createWaveInfo(SizeWave* size, uint display_time);
	
	//Phase 2 
	int					incrementPhase2WavePower();

	//Phase 3
	int					incrementPhase3WavePower();

	// Positions
	bombPosition   bomb_position;

	// ----------- GUI -------------------
	//Start/Exit Button
	SDL_Texture* start_image = nullptr;
	GuiImage* start_screen = nullptr;
	GuiImage* start_button = nullptr;
	GuiImage* close_button = nullptr;

	//Victory Screen
	SDL_Texture* victory_atlas = nullptr;
	GuiImage* victory_screen = nullptr;
	bool is_victory_screen_on = false;

	//Defeat Screen
	GuiImage* defeat_screen = nullptr;
	GuiImage* jim_dead = nullptr;
	GuiImage* base_destroyed = nullptr;
	SDL_Texture* defeat_atlas = nullptr;
	bool is_defeat_screen_on = false;

	//Ending Buttons
	GuiImage* retry_button = nullptr;
	GuiImage* exit_button = nullptr;

	// Info Message
	GuiInfo		*info_message;
	GuiTimer	*graphic_wave_timer;
};

#endif