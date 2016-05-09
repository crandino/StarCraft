#include "ParticleManager.h"
#include "App.h"
#include <math.h>
#include <time.h>
#include "Textures.h"
#include "Render.h"
#include "p2Log.h"
#include "Timer.h"
#include "EntityManager.h"
#include "Audio.h"

// PARTICLE MANAGER---------------

ParticleManager::ParticleManager() : Module()
{

}

ParticleManager::~ParticleManager()
{
	name.assign("particle_manager");
}

bool ParticleManager::awake(pugi::xml_node &node)
{
	LOG("Particle Manager: Awake");
	//textureFile.assign(node.child("particle_manager").first_attribute().as_string());

	return true;
}

bool ParticleManager::start()
{
	bool ret = true;
	LOG("Particle Manager: Start");
	//texture = app->tex->loadTexture(textureFile.c_str());

	//ret = loadParticlesFile(particle_file);

	return ret;
}

bool ParticleManager::update(float dt)
{
	bool ret = true;

	// TODO 2: Iterate the particles list, if update returns false, delete the particle. 

	std::list<Particle*>::iterator tmp = particleList.begin();

	while (tmp != particleList.end())
	{
		if ((*tmp)->update(dt) == false)
		{
			RELEASE((*tmp));
			tmp = particleList.erase(tmp);
		}
		else
		{
			++tmp;
		}
	}

	// TODO 2: Iterate the emisor list, if update returns false, delete the particle. 

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	while (tmp2 != emisorList.end())
	{
		if ((*tmp2)->update(dt) == false)
		{
			RELEASE((*tmp2));
			tmp2 = emisorList.erase(tmp2);
		}
		else
		{
			++tmp2;
		}
	}

	return ret;
}

bool ParticleManager::postUpdate()
{
	bool ret = true;

	//TODO 2: Iterate the particle list and call postUpdate

	std::list<Particle*>::reverse_iterator tmp = particleList.rbegin();

	for (; tmp != particleList.rend(); ++tmp)
	{
		(*tmp)->postUpdate();
	}

	//TODO 2: Iterate the emisor list and call postUpdate 

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	for (; tmp2 != emisorList.end(); ++tmp2)
	{
		(*tmp2)->postUpdate();
	}

	return ret;
}

bool ParticleManager::cleanUp()
{
	LOG("Particle Manager: CleanUp");
	//app->tex->unloadTexture(texture);

	//TODO 2: Iterate the particle list and clear, release the particle and clear the list.

	std::list<Particle*>::iterator tmp = particleList.begin();

	for (; tmp != particleList.end(); ++tmp)	
	RELEASE((*tmp));
	
	particleList.clear();

	//TODO 2: Iterate the emisor list and clear, release the particle and clear the list.

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	for (; tmp2 != emisorList.end(); ++tmp2)
	RELEASE((*tmp2));
	
	emisorList.clear();

	return true;
}

//TODO 2.1 : Uncomment when you finished TODO 2

bool ParticleManager::cleanActiveParticles()
{
	std::list<Particle*>::iterator tmp = particleList.begin();

	for (; tmp != particleList.end(); ++tmp)
		RELEASE((*tmp));

	particleList.clear();

	return true;
}

bool ParticleManager::cleanActiveEmisors()
{
	std::list<Emisor*>::iterator tmp = emisorList.begin();

	for (; tmp != emisorList.end(); ++tmp)
		RELEASE((*tmp));

	emisorList.clear();

	return true;
}

bool ParticleManager::loadParticlesFile(pugi::xml_document& file)
{
	bool ret = true;

	char* buff;
	int size = app->fs->load("Particles/particles.xml", &buff);
	pugi::xml_parse_result result = file.load_buffer(buff, size);
	RELEASE(buff);

	if (result == NULL)
	{
		ret = false;
		LOG("Could not load particles xml file. Pugi error: %s", result.description());
	}

	return ret;
}

Particle* ParticleManager::addParticle(const Particle& p, int x, int y, int offset_x, int offset_y, Uint32 secLife, SDL_Texture* texture, unsigned int sfx, uint32 delay)
{
	Particle* part = NULL;

	part = new Particle(p);
	part->offset.x = offset_x;
	part->offset.y = offset_y;
	part->position.x = (x - p.anim.peekCurrentFrame().w / 2) + offset_x;
	part->position.y = (y - p.anim.peekCurrentFrame().h / 2) + offset_y;
	part->on = p.on;
	part->initialPosition = p.position;
	part->alive = true;
	part->life = secLife;
	if (texture)
		part->image = texture;

	part->fx = sfx;
	part->timer.start();

	//TODO 3: insert the particle in the particleList
	particleList.push_back(part);

	return part;
}

Emisor* ParticleManager::addEmisor(Particle& p, int x, int y, float emisorDuration, Uint32 particleLife, int particleVelocity,
	float minAngle, float maxAngle, SDL_Texture* tex)  // If all particles are load at creation point
{
	Emisor* ret = NULL;

	ret = new Emisor(p);
	ret->position.set(x, y);
	ret->duration = emisorDuration;
	ret->particleEmited.life = particleLife;
	ret->velocity = particleVelocity;
	ret->minAngle = minAngle;
	ret->maxAngle = maxAngle;
	ret->particleEmited.image = tex;

	ret->timer.start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorLists
	emisorList.push_back(ret);

	return ret;
}

FireEmisor* ParticleManager::addFire(int x, int y, float duration)
{
	FireEmisor* ret = NULL;

	ret = new FireEmisor(duration);
	ret->position.set(x, y);

	ret->timer.start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorList
	emisorList.push_back(ret);

	return ret;
}

BurstEmisor* ParticleManager::addBurst(int x,int y)
{
	BurstEmisor* ret = NULL;

	ret = new BurstEmisor();
	ret->position.set(x, y);

	ret->timer.start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorList
	emisorList.push_back(ret);

	return ret;
}

//-----------------------------------------

// PARTICLE--------------------------------


Particle::Particle() : fx(0), life(0), fxPlayed(false), alive(false)
{
	position.setZero();
	speed.setZero();
}

Particle::Particle(const Particle& p)
{
	fx = p.fx;
	life = p.life;
	initialPosition = p.position;
	speed = p.speed;
	alive = p.alive;
	anim = p.anim;
	image = p.image;
}

Particle::~Particle()
{

}

void Particle::followPoint(int x, int y)
{
	position.x = x - anim.peekCurrentFrame().w / 2;
	position.y = y - anim.peekCurrentFrame().h / 2;
}

void Particle::destroyParticle()
{
	alive = false;
}

bool Particle::update(float dt)
{
	bool ret = true;

	if (life > 0)
	{
		// TODO 4: if timer is bigger than the life of the particle OR particle isn't alive, then return false
		if (timer.read() >= life * 1000 || alive == false)
		{
			ret = false;
		}
	}
	else
	{
		if (anim.finished() || alive == false)
			ret = false;
	}

	if ( alive == true && active == true)
	{
		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}

	return ret;
}
bool Particle::postUpdate()
{
	if (alive && active)
	{
		if (image != NULL)
		{
			//TODO 5: Get animation frame and then blit. 
			SDL_Rect sect = anim.getCurrentFrame();
			app->render->blit(image, position.x, position.y, &sect);
		}

		if (fxPlayed == false)
		{
			fxPlayed = true;
			app->audio->playFx(fx);
		}
	}


	return true;
}

void Particle::enable()
{
	active = true;
	timer.start();
}

void Particle::disable()
{
	active = false;
}

void Particle::setSpeed(float velocity, float minAngle, float maxAngle)
{
	float angle = minAngle + (rand() % (int)(maxAngle - minAngle));
	speed.x = velocity * cos(angle * (PI / 180));
	speed.y = velocity * sin(angle * (PI / 180));
}
//-----------------------------------------------------

// EMISOR----------------------------------------------

Emisor::Emisor()
{
	position.setZero();
	speed.setZero();
	active = alive = fxPlayed = false;
}

Emisor::Emisor(Particle& p)
{
	particleEmited = p;
	fx = p.fx;
	position.setZero();
	speed.setZero();
	fxPlayed = false;
}

Emisor::~Emisor()
{

}

bool Emisor::update(float dt) // If particles are created each frame
{
	bool ret = true;

	// TODO 4: if timer is bigger than the life of the emisor OR emisor isn't alive, then return false
	if (timer.read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}

	if (alive && active)
	{
		// TODO 5: Create a new particle with the particleEmited info and set his speed with method setSpeed
		Particle* q = app->particle->addParticle(particleEmited, position.x, position.y,offset.x,offset.y, particleEmited.life);
		q->setSpeed(velocity, minAngle, maxAngle);

		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}

	return ret;
}

bool Emisor::postUpdate()
{
	if (alive)
	{
		if (fxPlayed == false)
		{
			fxPlayed = true;
			app->audio->playFx(fx);
		}
	}

	return true;
}

void Emisor::setParticle(Particle& particle)
{
	particleEmited = particle;
}

void Emisor::enable()
{
	active = true;
	timer.start();
}

void Emisor::disable()
{
	active = false;
}

void Emisor::destroy()
{
	alive = false;
}
//---------------------------------------------------------

// FIRE EMISOR---------------------------------------------
FireEmisor::FireEmisor(float time) : Emisor()
{
	duration = time;

	pugi::xml_node fire1 = app->particle->particle_file.child("particles").child("fire1");

	int fireX = fire1.child("fire_anim").attribute("x").as_int();
	int fireY = fire1.child("fire_anim").attribute("y").as_int();
	int fireW = fire1.child("fire_anim").attribute("w").as_int();
	int fireH = fire1.child("fire_anim").attribute("h").as_int();
	int fireFPR = fire1.child("fire_anim").attribute("frames_per_row").as_int();
	int fireFPC = fire1.child("fire_anim").attribute("frames_per_column").as_int();
	int fireFrames = fire1.child("fire_anim").attribute("frame_number").as_int();
	float fireAnimSpeed = fire1.child("fire_anim").attribute("speed").as_float();
	bool fireLoop = fire1.child("fire_anim").attribute("loop").as_bool();
	float fireSpeedX = fire1.child("fire_speed").attribute("x").as_float();
	float fireSpeedY = fire1.child("fire_speed").attribute("y").as_float();
	const char* firePath = fire1.child("fire_file").attribute("value").as_string();

	fire.anim.setAnimations(fireX, fireY, fireW, fireH, fireFPR, fireFPC, fireFrames);
	fire.anim.speed = fireAnimSpeed;
	fire.anim.loop = fireLoop;
	fire.speed.set(fireSpeedX, fireSpeedY);
	fire.image = app->tex->loadTexture(firePath);
	fire.life = duration;

	int smokeX = fire1.child("smoke_anim").attribute("x").as_int();
	int smokeY = fire1.child("smoke_anim").attribute("y").as_int();
	int smokeW = fire1.child("smoke_anim").attribute("w").as_int();
	int smokeH = fire1.child("smoke_anim").attribute("h").as_int();
	int smokeFPR = fire1.child("smoke_anim").attribute("frames_per_row").as_int();
	int smokeFPC = fire1.child("smoke_anim").attribute("frames_per_column").as_int();
	int smokeFrames = fire1.child("smoke_anim").attribute("frame_number").as_int();
	float smokeAnimSpeed = fire1.child("smoke_anim").attribute("speed").as_float();
	bool smokeLoop = fire1.child("smoke_anim").attribute("loop").as_bool();
	float smokeSpeedX = fire1.child("smoke_speed").attribute("x").as_float();
	float smokeSpeedY = fire1.child("smoke_speed").attribute("y").as_float();
	float smokeFreq = fire1.child("smoke_frequence").attribute("value").as_float();
	float smokeStart = fire1.child("smoke_start").attribute("value").as_float();
	int smokeOffsetX = fire1.child("smoke_offset").attribute("x").as_int();
	int smokeOffsetY = fire1.child("smoke_offset").attribute("y").as_int();
	float smokeLife = fire1.child("smoke_life").attribute("value").as_float();
	const char* smokePath = fire1.child("smoke_file").attribute("value").as_string();

	smoke.anim.setAnimations(smokeX, smokeY, smokeW, smokeH, smokeFPR, smokeFPC, smokeFrames);
	smoke.anim.speed = smokeAnimSpeed;
	smoke.anim.loop = smokeLoop;
	smoke.speed.set(smokeSpeedX, smokeSpeedY);
	smokeFrequence = smokeFreq;
	smokeStart = smokeStart;
	smokeOffset.set(smokeOffsetX, smokeOffsetY);
	smoke.image = app->tex->loadTexture(smokePath);
	smoke.life = smokeLife;
}

FireEmisor::~FireEmisor()
{

}

bool FireEmisor::update(float dt)
{
	bool ret = true;

	if (timer.read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}
	if (alive && active)
	{
		if (!fireStarted)
		{
			fireStarted = true;
			app->particle->addParticle(fire, position.x, position.y,offset.x,offset.y, fire.life);
		}
		if (timer.read() >= smokeStart * 1000)
		{
			if (acumulator >= smokeFrequence * 1000)
			{
				app->particle->addParticle(smoke, position.x, position.y,smokeOffset.x,smokeOffset.y, smoke.life);
				acumulator = 0.0f;
			}
			acumulator += dt;
		}

		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}


	return ret;
}

bool FireEmisor::postUpdate()
{
	bool ret = true;

	if (alive && active)
	{
		if (!fxPlayed)
		{
			fxPlayed = true;
			app->audio->playFx(fx);
		}
	}

	return ret;
}
//---------------------------------------------------

//BURST EMISOR---------------------------------------
BurstEmisor::BurstEmisor() : Emisor()
{

	pugi::xml_node burst1 = app->particle->particle_file.child("particles").child("burst");

	int burstX = burst1.child("burst_anim").attribute("x").as_int();
	int burstY = burst1.child("burst_anim").attribute("y").as_int();
	int burstW = burst1.child("burst_anim").attribute("w").as_int();
	int burstH = burst1.child("burst_anim").attribute("h").as_int();
	int burstFPR = burst1.child("burst_anim").attribute("frames_per_row").as_int();
	int burstFPC = burst1.child("burst_anim").attribute("frames_per_column").as_int();
	int burstFrames = burst1.child("burst_anim").attribute("frame_number").as_int();
	float burstAnimSpeed = burst1.child("burst_anim").attribute("speed").as_float();
	bool burstLoop = burst1.child("burst_anim").attribute("loop").as_bool();
	float burstSpeedX = burst1.child("burst_speed").attribute("x").as_float();
	float burstSpeedY = burst1.child("burst_speed").attribute("y").as_float();
	const char* burstPath = burst1.child("burst_file").attribute("value").as_string();
	int burstLife = burst1.child("burst_life").attribute("value").as_int();
	float emisor_duration = burst1.child("emisor_duration").attribute("value").as_float();
	float emisor_velocity = burst1.child("emisor_velocity").attribute("value").as_float();
	float min_angle = burst1.child("min_angle").attribute("value").as_float();
	float max_angle = burst1.child("max_angle").attribute("value").as_float();

	burst.anim.setAnimations(burstX, burstY, burstW, burstH, burstFPR, burstFPC, burstFrames);
	burst.anim.speed = burstAnimSpeed;
	burst.anim.loop = burstLoop;
	burst.setSpeed(burstSpeedX, burstSpeedY);
	burst.image = app->tex->loadTexture(burstPath);
	burst.life = burstLife;
	emisor_burst.duration = emisor_duration;
	emisor_burst.velocity = emisor_velocity;
	emisor_burst.minAngle = min_angle;
	emisor_burst.maxAngle = max_angle;

}

BurstEmisor::~BurstEmisor()
{

}

bool BurstEmisor::update(float dt)
{
	bool ret = true;

	if (timer.read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}
	if (alive && active)
	{
		if (!burstStarted)
		{
			burstStarted = true;
			app->particle->addEmisor(burst, position.x, position.y, emisor_burst.duration, burst.life, emisor_burst.velocity, emisor_burst.minAngle,emisor_burst.maxAngle,burst.image);
		}
		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}


	return ret;
}

bool BurstEmisor::postUpdate()
{
	bool ret = true;

	if (alive && active)
	{
		if (!fxPlayed)
		{
			fxPlayed = true;
			app->audio->playFx(fx);
		}
	}

	return ret;
}
//----------------------------------------------------------------------
