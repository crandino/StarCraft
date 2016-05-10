#include "GuiLabel.h"
#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Textures.h"
#include "Input.h"


// class GuiLabel ---------------------------------------------------
GuiLabel::GuiLabel(const char* text, int kind_of_font, GUI_TYPES type) : GuiElements()
{
	setText(text,kind_of_font);
	this->type = type;
}

GuiLabel::GuiLabel(const char* text, int kind_of_font) : GuiElements()
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
void GuiLabel::draw() const
{
	iPoint p = getScreenPos();
	app->render->blit(texture, p.x, p.y, NULL, 0.0f);
}
