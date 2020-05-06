#include "j1CutsceneCharacters.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1CutsceneManager.h"


j1CutsceneCharacters::j1CutsceneCharacters() : j1Module()
{
	name.create("player");
}

j1CutsceneCharacters::~j1CutsceneCharacters()
{
}

bool j1CutsceneCharacters::Awake()
{
	return true;
}

bool j1CutsceneCharacters::Start()
{
	player_pos.x = 84;
	player_pos.y = 520;

	character1_pos.x = -50;
	character1_pos.y = 520;

	character2_pos.x = 1500;
	character2_pos.y = 520;

	player.active = false;
	character1.active = false;
	character2.active = false;
	
	input = true;

	return true;
}

bool j1CutsceneCharacters::PreUpdate(float dt)
{
	return true;
}


bool j1CutsceneCharacters::Update(float dt)
{
	if (input) 
	{
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) { player_pos.x -= 3; }
		
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) { player_pos.x += 3; }
		
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) { player_pos.y -= 3; }
		
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) { player_pos.y += 3; }	
	}
	
	App->render->DrawQuad({ player_pos.x, player_pos.y, 32, 32 }, 255, 180, 11, 255, true, true);
	App->render->DrawQuad({ character1_pos.x, character1_pos.y, 32, 32 }, 50, 200, 50, 255, true, true);
	App->render->DrawQuad({ character2_pos.x, character2_pos.y, 46, 46 }, 250, 53, 8, 255, true, true);
	

	return true;
}

bool j1CutsceneCharacters::PostUpdate(float dt)
{
	
	CutsceneListener();
	return true;
}

bool j1CutsceneCharacters::CleanUp()
{
	return true;
}

void j1CutsceneCharacters::CutsceneListener()
{
	if (player.active)
	{
		input = false;
		App->cutscene_manager->DoCutscene(player, player_pos);
	}

	if (character1.active)
	{
		App->cutscene_manager->DoCutscene(character1, character1_pos);
	}

	if (character2.active)
	{
		App->cutscene_manager->DoCutscene(character2, character2_pos);
	}
}


