#include "GuiImage.h"
#include "Textures.h"
#include "Input.h"

GuiImage::GuiImage(const SDL_Texture* texture) : GuiElements(), texture(texture)
{
	section.x = section.y = 0;
	app->tex->GetSize(texture, (unsigned int&)section.w, (unsigned int&)section.h);

	setSize(section.w, section.h);
	type = IMAGE;
}

// --------------------------
GuiImage::GuiImage(const SDL_Texture* texture, const SDL_Rect& section) : GuiElements(), texture(texture), section(section)
{
	setSize(section.w, section.h);
}

GuiImage::GuiImage(GuiImage* image, iPoint position) : GuiElements()
{
	
}

// --------------------------
GuiImage::~GuiImage()
{}

// --------------------------
void GuiImage::setSection(const SDL_Rect& section)
{
	this->section = section;
}

// --------------------------
void GuiImage::draw() const
{
	iPoint p = getScreenPos();
	if (parent && parent->cut_childs)
	{
		SDL_Rect r = parent->getScreenRect();
		app->render->SetViewPort({ r.x, r.y, r.w, r.h });
		p = getLocalPos();
	}
	app->render->blit(texture, p.x, p.y, (SDL_Rect*)&section, 0.0f);

	if (parent && parent->cut_childs)
		app->render->ResetViewPort();
}

void GuiImage::draw_static() const
{
	app->render->blit(texture, rect.x + app->render->camera.x, rect.y + app->render->camera.y, (SDL_Rect*)&section, 0.0f);
}