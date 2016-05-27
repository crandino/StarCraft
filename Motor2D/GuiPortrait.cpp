#include "GuiPortrait.h"
#include "Textures.h"
#include "Input.h"
#include "Animation.h"
#include "Map.h"

GuiPortrait::GuiPortrait(const SDL_Texture* texture, Animation anim) : GuiElements(), texture(texture)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	setSize(section.w, section.h);
	type = PORTRAIT;
}

GuiPortrait::~GuiPortrait()
{

}

void GuiPortrait::setSection(const SDL_Rect& section)
{
	this->section = section;
}

// --------------------------
void GuiPortrait::draw() const
{
	iPoint p = getScreenPos(); 
	app->render->blit(texture, p.x, p.y, &(current_animation->getCurrentFrame()), 0.0f);
}
	
void GuiPortrait::draw_static() const
{
	app->render->blit(texture, rect.x + app->render->camera.x, rect.y + app->render->camera.y, (SDL_Rect*)&section, 0.0f);
}