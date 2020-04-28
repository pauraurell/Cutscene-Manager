#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Player.h"
#include "j1CutsceneManager.h"


j1CutsceneManager::j1CutsceneManager() : j1Module()
{
	name.create("cutscene");
}

// Destructor
j1CutsceneManager::~j1CutsceneManager()
{}

// Called before render is available
bool j1CutsceneManager::Awake(pugi::xml_node& config)
{
	bool ret = true;

	LOG("Loading Scene");

	return ret;
}

// Called before the first frame
bool j1CutsceneManager::Start()
{
	fase = None;
	alpha = 0;
	int bar_height = 100;
	top_rect.x = 0; top_rect.y = 0; top_rect.w = App->win->width; top_rect.h = bar_height;
	down_rect.x = 0; down_rect.y = App->win->height - bar_height; down_rect.w = App->win->width; down_rect.h = bar_height;
	
	LOG("Start scene");

	return true;
}

// Called each loop iteration
bool j1CutsceneManager::PreUpdate(float dt)
{
	return true;
}

// Called each loop iteration
bool j1CutsceneManager::Update(float dt)
{

	switch (fase)
	{
		case Drawing: BlackBars_Draw();
	
	}


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		fase = Drawing;
	}

	return true;
}

// Called each loop iteration
bool j1CutsceneManager::PostUpdate(float dt)
{
	return true;
}

// Called before quitting
bool j1CutsceneManager::CleanUp()
{

	LOG("Cutscene Manager Clean Up");

	return true;
}

void j1CutsceneManager::BlackBars_FadeIn()
{
	/*SDL_Rect top_rect, down_rect;
	int bar_height = 100;
	alpha += 3;
	top_rect.x = 0; top_rect.y = 0; top_rect.w = App->win->width; top_rect.h = bar_height;
	down_rect.x = 0; down_rect.y = App->win->height - bar_height; down_rect.w = App->win->width; down_rect.h = bar_height;
	App->render->DrawQuad(top_rect, 0, 0, 0, alpha, true, false);
	App->render->DrawQuad(down_rect, 0, 0, 0, alpha, true, false);
	if (alpha >= 255) { alpha = 255; }*/
}

void j1CutsceneManager::BlackBars_Draw()
{
	alpha = 255;
	App->render->DrawQuad(top_rect, 0, 0, 0, alpha, true, false);
	App->render->DrawQuad(down_rect, 0, 0, 0, alpha, true, false);
}