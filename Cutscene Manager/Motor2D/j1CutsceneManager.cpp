#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1CutsceneCharacters.h"
#include "j1CutsceneManager.h"


j1CutsceneManager::j1CutsceneManager() : j1Module()
{
	name.create("cutscene");
}

// Destructor
j1CutsceneManager::~j1CutsceneManager()
{}


// Called before the first frame
bool j1CutsceneManager::Start()
{
	black_bars.fase = None;
	black_bars.alpha = 0;
	int bar_height = 100;

	black_bars.top_rect.x = 0;
	black_bars.top_rect.y = -bar_height;
	black_bars.top_rect.w = App->win->width;
	black_bars.top_rect.h = bar_height;

	black_bars.down_rect.x = 0;
	black_bars.down_rect.y = App->win->height;
	black_bars.down_rect.w = App->win->width;
	black_bars.down_rect.h = bar_height;

	result = data.load_file("CutsceneEditor.xml");
	cutsceneManager = data.document_element();

	LOG("Starting Cutscene Manager");

	return true;
}

// Called each loop iteration
bool j1CutsceneManager::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool j1CutsceneManager::PostUpdate(float dt)
{

	//Black Bars Drawing
	switch (black_bars.fase)
	{
	case FadeIn:
		black_bars.FadeIn();
		break;
	case Drawing:
		black_bars.Draw();
		break;
	case FadeOut:
		black_bars.FadeOut();
		break;
	}
	return true;
}

// Called before quitting
bool j1CutsceneManager::CleanUp()
{

	return true;
}

void BlackBars::FadeIn()
{
	alpha += 3;
	top_rect.y++;
	down_rect.y--;
	Draw();
	if (alpha >= 255) { alpha = 255;   fase = Drawing; }
}

void BlackBars::Draw()
{
	top_rect.y = 0;
	down_rect.y = App->win->height - 100;
	App->render->DrawQuad(top_rect, 0, 0, 0, alpha, true, false);
	App->render->DrawQuad(down_rect, 0, 0, 0, alpha, true, false);
}

void BlackBars::FadeOut()
{
	alpha -= 3;
	Draw();
	if (alpha == 0) { alpha = 0; fase = None; }
}

void j1CutsceneManager::StartCutscene(string name)
{
	if (!App->characters->player.active)
	{
		for (pugi::xml_node cutscene = cutsceneManager.child("cutscene"); cutscene; cutscene = cutscene.next_sibling("cutscene"))
		{
			if (cutscene.attribute("name").as_string() == name)
			{
				LoadSteps(cutscene);

				if (black_bars.fase == None) { black_bars.fase = FadeIn; }
			}
		}
		if (App->characters->player.active) { UpdateStep(App->characters->player); }
		if (App->characters->character1.active) { UpdateStep(App->characters->character1); }
		if (App->characters->character2.active) { UpdateStep(App->characters->character2); }
	}
}

bool j1CutsceneManager::LoadSteps(pugi::xml_node node)
{
	Step* s = new Step;

	for (pugi::xml_node step = node.child("step"); step; step = step.next_sibling("step"))
	{
		s->objective = step.attribute("objective").as_string();
		s->position.x = step.attribute("x").as_int();
		s->position.y = step.attribute("y").as_int();
		s->speed.x = step.attribute("vel_x").as_int();
		s->speed.y = step.attribute("vel_y").as_int();

		if (s->objective == "player")
		{
			App->characters->player.steps.push_front(*s);
			App->characters->player.active = true;
		}

		if (s->objective == "character1")
		{
			App->characters->character1.steps.push_front(*s);
			App->characters->character1.active = true;
		}

		if (s->objective == "character2")
		{
			App->characters->character2.steps.push_front(*s);
			App->characters->character2.active = true;
		}
	}
	delete s;

	return true;
}

void j1CutsceneManager::DoCutscene(CutsceneObject& character, iPoint& objective_position)
{
	Step step = character.current_step;

	Movement(step, objective_position);

	if (step.position != character.steps.front().position)
	{
		if (step.position == objective_position)
		{
			UpdateStep(character);
		}
	}
	else { FinishCutscene(character); }
}

void j1CutsceneManager::Movement(Step& step, iPoint& objective_position)
{
	if (step.position.x > objective_position.x)
	{
		if (step.position.x - objective_position.x > step.speed.x)
		{
			objective_position.x += step.speed.x;
		}
		else { objective_position.x++; }
	}

	else if (step.position.x < objective_position.x)
	{
		if (objective_position.x - step.position.x > step.speed.x)
		{
			objective_position.x -= step.speed.x;
		}
		else { objective_position.x--; }
	}

	if (step.position.y > objective_position.y)
	{
		if (step.position.y - objective_position.y > step.speed.y)
		{
			objective_position.y += step.speed.y;
		}
		else { objective_position.y++; }
	}

	else if (step.position.y < objective_position.y)
	{
		if (objective_position.y - step.position.y > step.speed.y)
		{
			objective_position.y -= step.speed.y;
		}
		else { objective_position.y--; }
	}
}

void j1CutsceneManager::UpdateStep(CutsceneObject& character)
{
	if (character.active)
	{
		character.current_step.position.x = character.steps.back().position.x;
		character.current_step.position.y = character.steps.back().position.y;
		character.current_step.speed.x = character.steps.back().speed.x;
		character.current_step.speed.y = character.steps.back().speed.y;
	}

	if (character.steps.empty() == false)
	{
		character.steps.pop_back();
	}
}

void j1CutsceneManager::FinishCutscene(CutsceneObject& character)
{
	character.active = false;
	App->characters->input = true;

	if (black_bars.fase == Drawing) { black_bars.fase = FadeOut; }
}


