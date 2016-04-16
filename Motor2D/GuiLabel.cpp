#include "GuiLabel.h"
#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Textures.h"

GuiLabel::GuiLabel() : GuiElements()
{
	type = LABEL;
	texture = NULL;
	text = "";
}

GuiLabel::GuiLabel(const char* txt, const int x, const int y) : GuiElements()
{
	type = LABEL;
	text = txt;

	texture = app->fonts->print(text.data());

	rect.x = x;
	rect.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}



// Destructor
GuiLabel::~GuiLabel()
{}

// Called before render is available
bool GuiLabel::update(float dt)
{
	bool ret = true;


	if (texture != NULL)
	{
		iPoint cam_pos(app->render->camera.x, app->render->camera.y);
		iPoint screen_pos = getScreenPos();
		app->render->blit(texture, screen_pos.x - cam_pos.x, screen_pos.y - cam_pos.y);
	}

	return ret;
}

bool GuiLabel::cleanUp()
{
	bool ret = true;

	if (texture != NULL)
	{
		app->tex->unloadTexture(texture);
	}


	return ret;
}


void GuiLabel::print(string _text, bool isPassword)
{
	app->tex->unloadTexture(texture);

	text = _text;
	if (text != "")
	{
		if (isPassword == false)
		{
			texture = app->fonts->print(text.data());
		}
		else
		{
			password = text;
			password.replace(password.begin(), password.end() - strlen(text.data()), strlen(text.data()), '*');
			texture = app->fonts->print(password.data());
		}

		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}
	else
		texture = NULL;
}

string GuiLabel::getText(bool is_password) const
{
	if (is_password)
		return password;
	else
		return text;
}