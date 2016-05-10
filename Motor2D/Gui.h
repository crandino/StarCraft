#ifndef __GUI_H__
#define __GUI_H__

#include "App.h"
#include "Module.h"
#include "Render.h"
#include "Animation.h"
#include "EntityManager.h"

class GuiCursor;
class GuiImage;
class GuiLabel;
class GuiMinimap;
class GuiTimer;
using namespace std;


enum GUI_EVENTS
{
	LISTENING_ENDS,
	MOUSE_ENTERS,
	MOUSE_LEAVES,
	MOUSE_LCLICK_DOWN,
	MOUSE_LCLICK_DOWN_REPEAT,
	MOUSE_LCLICK_UP,
	MOUSE_RCLICK_DOWN,
	MOUSE_RCLICK_UP,
	GAIN_FOCUS,
	LOST_FOCUS,
    INPUT_CHANGED,
	INPUT_SUBMIT,
    VALUE_CHANGED,
	SAVE_POS_THUMB,
	LOAD_POS_THUMB
};

enum GUI_TYPES
{
	UNKNOWN,
	IMAGE,
	CURSOR,
	LABEL,
	TEXTMESSAGES,
	MINIMAP,
	TIMER

};

// ---------------------------------------------------
class Gui : public Module
{
public:

	Gui();

	// Destructor
	virtual ~Gui();

	// Called when before render is available
	bool awake(pugi::xml_node&);

	// Call before first frame
	bool start();

	// Called before all Updates
	bool preUpdate();

	// Called each loop iteration
	bool update(float dt);

	// Called after all Updates
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	// Gui creation functions
	GuiImage* createImage(const char* filename);
	GuiImage* createImage(const SDL_Texture* texture, const SDL_Rect& atlas_section);
	GuiCursor* createCursor(const SDL_Texture* texture);
	GuiLabel* createLabel(const char* text, int kind_of_font);
	GuiLabel* createLabel(const char* text, int kind_of_font, GUI_TYPES type);
	GuiMinimap* createMinimap(SDL_Rect rect, const char *pathTex);
	GuiTimer* createTimer(iPoint pos, const char *pathTex, Timer &timer_associated);

	const GuiElements* findMouseHover();
	const SDL_Texture* getAtlas() const;

	SDL_Rect mouseQuad(iPoint init_mouse);

	void onGui(GuiElements* ui, GUI_EVENTS event);

	// Variables for Cursor-------------------
	GuiCursor *cursor;
	iPoint cursor_offset;
	iPoint map_limits;
	float scroll_speed;
	fPoint last_attack_position;
	list<fPoint> lasts_attack_position;
	Timer timer_to_ping_attack;

	//Sounds
	unsigned int fx_click_1;
	unsigned int fx_click_error;
	unsigned int fx_not_enough_minerales;

	//HUD Ingame----------------------------- 
	GuiImage* ui_terran = nullptr;
	GuiImage* rectangle_map = nullptr;
	GuiImage* rectangle_command = nullptr;
	GuiImage* rectangle_command_2 = nullptr;
	GuiImage* rectangle_command_3 = nullptr;
	GuiImage* rectangle_command_4 = nullptr;
	GuiImage* rectangle_command_5 = nullptr;
	GuiImage* rectangle_command_6 = nullptr;
	GuiImage* rectangle_command_7 = nullptr;
	GuiImage* rectangle_command_8 = nullptr;
	GuiImage* rectangle_command_9 = nullptr;


	//Command Center HUD--------------------
	GuiImage* ui_create_bot = nullptr;
	GuiImage* ui_create_builds = nullptr;
	GuiImage* ui_create_bunker = nullptr;
	//GuiImage* ui_create_turrets = nullptr;
	GuiImage* ui_create_factory = nullptr;
	//GuiImage* ui_create_starport = nullptr;
	GuiImage* ui_create_barraks = nullptr;

	//Control Barracks and Factories
	bool barrackAlive = false;
	bool factoryAlive = false;

	//Barracks HUD-------------------------
	GuiImage* ui_create_marine = nullptr;
	GuiImage* ui_create_medic = nullptr;
	GuiImage* ui_create_firebat = nullptr;
	GuiImage* ui_set_bomb = nullptr;

	//Factory HUD-----------------------
	GuiImage* ui_create_tank = nullptr;

	bool buildingMenuOpened = false;
	bool commandCenterOpened = false;
	bool barrackMenuOpened = false;
	bool factoryMenuOpened = false;

	void openBuildingMenu();

	void controlIconsSprite();

	//Wireframes and Info
	//Wireframes
	SDL_Texture* atlas_wireframes = nullptr;
	//Bunkers
	GuiLabel* bunkerName = nullptr;
	GuiImage* bunkerWireframe = nullptr;
	GuiLabel* bunkerInfo = nullptr;
	GuiLabel* bunkerInfo2 = nullptr;
	//Command Center
	GuiLabel* commandCenterName = nullptr;
	GuiImage* commandCenterWireframe = nullptr;
	GuiLabel* commandCenterInfo = nullptr;
	//Factory
	GuiLabel* factoryName = nullptr;
	GuiImage* factoryWireframe = nullptr;
	GuiLabel* factoryInfo = nullptr;
	//Barracks
	GuiLabel* barrackName = nullptr;
	GuiImage* barrackWireframe = nullptr;
	GuiLabel* barrackInfo = nullptr;
	//Marine
	GuiImage* marineWireframe = nullptr;
	//Medic
	GuiImage* medicWireframe = nullptr;
	//Firebat
	GuiImage* firebatWireframe = nullptr;
	//Tank
	GuiImage* tankWireframe = nullptr;
	//Raynor
	GuiImage* raynorWireframe = nullptr;


	//Bunkers HUD---------------------------
	GuiImage* ui_leave_bunker = nullptr;
	list<Bunker*> bunker_to_leave;

	//HUD Label-----------------------------
	GuiLabel* number_of_wave = nullptr;

	//MESSAGES FOR THE PLAYER
	GuiLabel* preparation_message = nullptr;
	GuiLabel* preparation_message2 = nullptr;
	GuiLabel* second_phase_message1 = nullptr;
	GuiLabel* second_phase_message2 = nullptr;

	//HUD  Mineral and Gass-----------------
	GuiImage* ui_mineral = nullptr;
	GuiLabel* number_of_minerals = nullptr;
	GuiImage* ui_gas = nullptr;
	GuiLabel* number_of_gass = nullptr;


	//HUD Info SCV and Bunker-----------------
	GuiImage* info_scv = nullptr;
	GuiImage* info_bunker = nullptr;

	// HUD Graphic Timers
	GuiTimer *wave_timer;

	// HUD Minimap
	GuiMinimap* mini_map;

	//Raynor indicator Image
	GuiImage* raynor_indicator = nullptr;

	//Variables for CircleSelection. There are 10 size selection
	/*W_22 = { 3, 4, 22, 13 }; Marine, Zergling
	W_32 = { 28, 9, 32, 19 }; Mutalisk
	W_48 = { 64, 5, 48, 29 };
	W_62 = { 116, 2, 62, 37}; Tank
	W_72 = { 184, 2, 72, 43};
	W_94 = { 261, 1, 94, 56};
	W_94 = { 261, 1, 94, 56};
	W_110 = { 361, 1, 110, 66};
	W_122 =  {376, 74, 122, 73};
	W_146 = {226, 66, 146, 88};
	W_222 = { 2, 44, 222, 134};*/
	SDL_Texture*	circles_of_selection;

	// Variables for life of entities;
	SDL_Texture* lifes_tex;
	SDL_Rect	 green_life;
	SDL_Rect	 yellow_life;
	SDL_Rect	 red_life;
	SDL_Rect     white_life;
	

private:
		
	bool debug = false;
	list<GuiElements*> elements;
	const GuiElements* focus = nullptr;
	SDL_Texture* atlas = nullptr;
	SDL_Texture* terran_console = nullptr;
	string atlas_file_name;
	void drawHudSelection(SPECIALIZATION  selection);

	SDL_Texture *path_walkability;
};

#endif