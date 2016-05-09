#include "GuiLabel.h"
#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Textures.h"
#include "Input.h"


// class GuiLabel ---------------------------------------------------
GuiLabel::GuiLabel(const char* text, int kind_of_font, iPoint pos) : GuiElements()
{
	this->pos = pos;
	setText(text,kind_of_font);
	type = LABEL;
}

GuiLabel::GuiLabel(const char* text, int kind_of_font)
{
		setText(text, kind_of_font);
		type = LABEL;
}

// --------------------------
GuiLabel::~GuiLabel()
{
	if (texture != nullptr && texture != app->gui->getAtlas())
		app->tex->unloadTexture(texture);
}



// --------------------------
void GuiLabel::setText(const char* text, int font)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);


	texture = app->fonts->print(text, { 255, 255, 255, 255 },font);
	int w, h;
	app->tex->GetSize(texture, (uint&)w, (uint&)h);
	setSize(w, h);
}

// --------------------------
const SDL_Texture* GuiLabel::getTexture() const
{
	return texture;
}

// --------------------------
void GuiLabel::draw()
{
	app->render->blit(texture, pos.x, pos.y, NULL, 0.0f);
}
