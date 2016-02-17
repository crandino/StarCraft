#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Window.h"

#include "SDL/include/SDL.h"


Window::Window() : Module()
{
	window = NULL;
	screen_surface = NULL;
	name.create("window");
}

// Destructor
Window::~Window()
{ }

// Called before render is available
bool Window::awake(pugi::xml_node &node)
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;
		width = node.child("resolution").attribute("width").as_uint();
		height = node.child("resolution").attribute("height").as_uint();
		scale = node.child("resolution").attribute("scale").as_uint();

		if (node.child("properties").attribute("fullscreen").as_bool())
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (node.child("properties").attribute("borderless").as_bool())
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if (node.child("properties").attribute("resizable").as_bool())
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if (node.child("properties").attribute("windowed").as_bool())
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
			setTitle(node.child("name").child_value());
		}
	}

	return ret;
}

// Called before quitting
bool Window::cleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void Window::setTitle(const char* new_title)
{
	//title.create(new_title);
	SDL_SetWindowTitle(window, new_title);
}

void Window::getWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

uint Window::getScale() const
{
	return scale;
}