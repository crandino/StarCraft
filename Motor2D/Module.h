// ----------------------------------------------------
// Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __MODULE_H__
#define __MODULE_H__

#include "p2SString.h"
#include "PugiXml\src\pugixml.hpp"

class App;

class Module
{
public:

	Module() : active(false)
	{}

	virtual ~Module()
	{}

	void init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool awake(pugi::xml_node &node)
	{
		return true;
	}

	// Called before the first frame
	virtual bool start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool preUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool postUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool cleanUp()
	{
		return true;
	}

	// Load / Save
	virtual bool load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool save(pugi::xml_node&) const 
	{
		return true;
	}

public:

	p2SString	name;
	bool		active;

};

#endif // __MODULE_H__
