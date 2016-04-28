#include "GuiElements.h"
#include "Input.h"

// class Gui ---------------------------------------------------
GuiElements::GuiElements()
{ }

void GuiElements::setLocalPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void GuiElements::center()
{
	int frame_w = (parent) ? parent->getLocalRect().w : app->render->camera.w;
	int frame_h = (parent) ? parent->getLocalRect().h : app->render->camera.h;

	setLocalPos(frame_w / 2 - rect.w / 2, frame_h / 2 - rect.h / 2);
}

void GuiElements::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

SDL_Rect GuiElements::getLocalRect() const
{
	return rect;
}

SDL_Rect GuiElements::getScreenRect() const
{
	if (parent != nullptr)
	{
		iPoint p = getScreenPos();
		return{ p.x, p.y, rect.w, rect.h };
	}
	return rect;
}

iPoint GuiElements::getScreenPos() const
{
	if (parent != nullptr)
		return parent->getScreenPos() + iPoint(rect.x, rect.y);
	else
		return iPoint(rect.x, rect.y);
}

iPoint GuiElements::getLocalPos() const
{
	return iPoint(rect.x, rect.y);
}


void GuiElements::debugDraw() const
{
	SDL_Rect r = getScreenRect();
	app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, false);
}

void GuiElements::setListener(Module* module)
{
	if (listener != nullptr)
		listener->onGui(this, LISTENING_ENDS);

	listener = module;
}

Module* GuiElements::getListener()const
{
	return listener;
}

void GuiElements::checkInput(const GuiElements* mouse_hover, const GuiElements* focus)
{
	bool inside = (mouse_hover == this);

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			listener->onGui(this, (inside) ? MOUSE_ENTERS : MOUSE_LEAVES);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
				listener->onGui(this, MOUSE_LCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
				listener->onGui(this, MOUSE_LCLICK_DOWN_REPEAT);

			if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
				listener->onGui(this, MOUSE_LCLICK_UP);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
				listener->onGui(this, MOUSE_RCLICK_DOWN);

			if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_UP)
				listener->onGui(this, MOUSE_RCLICK_UP);
		}

		if (draggable == true && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
		{
			iPoint p = getLocalPos();
			iPoint motion;
			motion = app->input->getMouseMotion();
			setLocalPos(p.x + motion.x, p.y + motion.y);
		}
	}

	if (have_focus != (focus == this))
	{
		if (listener != nullptr)
		{
			if (focus == this)
				listener->onGui(this, GAIN_FOCUS);
			else
				listener->onGui(this, LOST_FOCUS);
		}
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_DOWN)
			listener->onGui(this, MOUSE_LCLICK_DOWN);

		if (app->input->getKey(SDL_SCANCODE_RETURN) == KeyState::KEY_UP)
			listener->onGui(this, MOUSE_LCLICK_UP);
	}
}

GUI_TYPES GuiElements::getType()const
{
	return type;
}