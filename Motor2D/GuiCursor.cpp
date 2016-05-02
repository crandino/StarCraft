#include "GuiCursor.h"
#include "Input.h"

//CURSOR------------------------------------------------
GuiCursor::GuiCursor(const SDL_Texture* texture)
{
	this->texture = texture;
	current_animation = &idle;
	setSize(41, 43);

	// IDLE animation
	idle.frames.push_back({ 2, 2, 40, 42 });
	idle.frames.push_back({ 46, 2, 40, 42 });
	idle.frames.push_back({ 90, 2, 40, 42 });
	idle.frames.push_back({ 134, 2, 40, 42 });
	idle.frames.push_back({ 178, 2, 40, 42 });
	idle.speed = 0.01f;
	idle.loop = true;

	//Selection
	selection_anim.frames.push_back({ 310, 48, 40, 42 });
	selection_anim.speed = 0.01f;
	selection_anim.loop = true;

	// LEFT displacement animation
	// X positions has been modified to perfectly adapt to the screen
	/*left_disp.frames.push_back({ 178, 232, 40, 42 });
	left_disp.frames.push_back({ 222, 232, 40, 42 });*/
	left_disp.frames.push_back({ 166, 232, 40, 42 });
	left_disp.frames.push_back({ 210, 232, 40, 42 });
	left_disp.speed = 0.02f;
	left_disp.loop = true;

	//RIGHT displacement animation
	// X positions has been modified to perfectly adapt to the screen
	/*right_disp.frames.push_back({ 530, 232, 40, 42 });
	right_disp.frames.push_back({ 574, 232, 40, 42 });*/
	right_disp.frames.push_back({ 542, 232, 40, 42 });
	right_disp.frames.push_back({ 586, 232, 40, 42 });
	right_disp.speed = 0.02f;
	right_disp.loop = true;

	//UP displacement animation
	// Y positions has been modified to perfectly adapt to the screen
	/*up_disp.frames.push_back({ 354, 232, 40, 42 });
	up_disp.frames.push_back({ 398, 232, 40, 42 });*/
	up_disp.frames.push_back({ 354, 220, 40, 42 });
	up_disp.frames.push_back({ 398, 220, 40, 42 });
	up_disp.speed = 0.02f;
	up_disp.loop = true;

	//DOWN displacement animation
	// Y positions has been modified to perfectly adapt to the screen
	/*down_disp.frames.push_back({ 2, 232, 40, 42 });
	down_disp.frames.push_back({ 46, 232, 40, 42 });*/
	down_disp.frames.push_back({ 2, 244, 40, 42 });
	down_disp.frames.push_back({ 46, 244, 40, 42 });
	down_disp.speed = 0.02f;
	down_disp.loop = true;

	type = CURSOR;
}

GuiCursor::~GuiCursor(){

}

void GuiCursor::update()
{
	iPoint p;
	app->input->getMousePosition(p);
	setLocalPos(p.x, p.y);
}

void GuiCursor::draw()const
{
	SDL_Rect r = getLocalRect();
	// To perfectly sync the tip cursor with the mouse, we need 20 pixels left and 17 pixels up
	app->render->blit(texture, r.x - 20, r.y - 17, &(current_animation->getCurrentFrame()), 0.0f);
}

void GuiCursor::debugDraw() const
{
	SDL_Rect r = getScreenRect();
	app->render->DrawQuad({ r.x, r.y, r.w, r.h }, 255, (have_focus) ? 255 : 0, 0, 255, false, false);
}
