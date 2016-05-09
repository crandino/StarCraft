#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Audio.h"
#include "Collision.h"
#include "GameManager.h"
#include "ParticleManager.h"
#include "FogOfWar.h"
#include "SDL\include\SDL.h"

#define TIME_TO_CHECK 100.0f

enum STATE
{
	IDLE,
	MOVE,
	MOVE_ALERT,
	MOVE_ALERT_TO_ATTACK,
	ATTACK,
	DYING,
	WAITING_PATH_MOVE,
	WAITING_PATH_MOVE_ALERT,
	WAITING_PATH_MOVE_ALERT_TO_ATTACK,
	
	// TANK STATES
	SIEGE_MODE_ON,
	SIEGE_MODE_OFF,
	IDLE_SIEGE_MODE,
	ATTACK_SIEGE_MODE
};

class Entity
{
private:

	bool debug = true;

public:

	// Positions and information
	fPoint			pos;						// World position of Entity. Upper_left corner.
	fPoint			center;						// World positoin of Entity. Center
	iPoint			tile_pos;					// Map position (tiles) of Entity
	uint			id;							// Identifier for Entity Manager
	Vector2D<int>   direction;					// Where is the entity looking at?
	float			angle;						// Looking right means 0 degrees, increasing counter-clock wise
	bool			to_delete;					// Entity Manager will delete this entity if it's true

	// Collider
	Collider*       coll;
	iPoint			collider_offset;			// Useful to correctly place the collider rect

	// Characterization and behaviour
	FACTION			faction;					// Player or computer
	ENTITY_TYPE		type;						// Unit or building	
	SPECIALIZATION  specialization;				// Marines, zerglings, bunkers, ...
	STATE			state;						// Idle, attack, move, ...

	// Graphics
	SDL_Texture		*tex;
	Animation		*current_animation;
	Particle		*particle;					//Pointer to control the particles on entities
	Particle		*particle_aux;				//Auxiliar pointer to control more particles
	iPoint			particle_offset;
	int		     	tex_width, tex_height;		// Dimensions of the sections of the frames

	// UI paramters
	SDL_Rect        selection_type;				// Section of the texture that contains circle selections
	iPoint		    circle_selection_offset;    // Useful to correctly place the circle selection
	iPoint			offset_life;				// Useful to correctly place the life's bar
	
	// Lifes attributes
	uint			max_hp;						// Max life value of this entity
	int             current_hp;					// The current life of the entity
	uint            max_hp_bars;				// How many green bars that current_hp represents?

	// Attack values and properties
	Entity			*target_to_attack = NULL;		// Which entity to attack
	float			damage;							// Value of its weapons
	float			damage_multiplier = 1.0f;
	float			speed_multiplier = 1.0f;
	Timer			timer_attack;					// To check time between attacks
	float			attack_frequency;				// How many miliseconds will wait to attack again?
	float			attack_frequency_multiplier = 1.0f;
	int				range_of_vision;				// How far can this entity detect another entity?
	int				range_to_attack;				// How far can this entity attack another entity?

	Timer			timer_to_check;					// Time between IA checking
	float			time_to_die;
	
	// Constructors
	Entity()
	{
		to_delete = false;
		timer_to_check.start();
		timer_attack.start();	
		state = IDLE;
		angle = 0.0f;
		direction.setToZero();
	};

	// Destructor
	virtual ~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	virtual bool start()
	{
		return true;
	}

	virtual bool update(float dt)
	{
 		return true;
	}

	virtual Entity* searchNearestEnemy()
	{
		return app->entity_manager->searchNearestEntityInRange(this);
	}

	virtual Entity* searchNearestAlly()
	{
		return app->entity_manager->searchNearestEntityInRange(this, true);
	}

	virtual Entity* searchAllyToHeal(bool search_only_buildings = false)
	{
		return app->entity_manager->searchAllyToHeal(this, search_only_buildings);
	}

	virtual list<Entity*> searchEntitiesInRange(Entity* origin, float area_range, bool can_attack_to_flying = true)
	{
		return app->entity_manager->searchEntitiesInRange(origin, true, area_range, can_attack_to_flying);
	}

	virtual Entity* searchEnemy()
	{
		return app->entity_manager->searchEnemyToAttack(this);
	}

	virtual void draw()
	{
		//FOG_OF_WAR 4 - "Draw" function of a unit. Called each frame for each unit.
		//Rendering the unit only if it is visible
		if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

	virtual void setAnimationFromDirection()
	{ }

};

#endif !__ENTITY_H__