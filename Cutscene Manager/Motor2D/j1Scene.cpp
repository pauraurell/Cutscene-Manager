#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1CutsceneCharacters.h"
#include "j1CutsceneManager.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	bool ret = true;

	LOG("Loading Scene");
	pugi::xml_node map;

	for (map = config.child("map"); map; map = map.next_sibling("map")) {
		p2SString lvlname;
		lvlname.create(map.attribute("name").as_string());
	}
	
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	LOG("Start scene");

	current_level = "map.tmx";
	map_coordinates = { 0, 0 };

	App->map->Load(current_level.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate(float dt)
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	int x, y;
	App->input->GetMousePosition(x, y);
	mouse_position = App->render->ScreenToWorld(x, y);

	iPoint player = App->characters->player_pos;

	if (!App->render->cinematic_camera.active)
	{
		App->render->camera.x = -player.x + App->win->width / 2;
		App->render->camera.y = -player.y + App->win->height / 2;
		SceneLimits();
	}
	//Camera following the player and limits

	iPoint MapPos;
	list<MapLayer*>::iterator Layer_list;
	MapLayer* layer;

	for (Layer_list = App->map->data.layers.begin(); Layer_list != App->map->data.layers.end(); ++Layer_list)
	{
		layer = *Layer_list;
		if (layer->returnPropValue("CutsceneTrigger") == 1) 
		{
			MapPos = App->map->WorldToMap(App->characters->player_pos.x, App->characters->player_pos.y);
			if (layer->Get(MapPos.x, MapPos.y) != 0)
			{
				App->cutscene_manager->StartCutscene("test2");
			}			
			
		}
	}

	//Draw the map
	App->map->Draw();
	map_coordinates = App->map->WorldToMap(mouse_position.x, mouse_position.y);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->cutscene_manager->StartCutscene("test1");
	}

	else if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->cutscene_manager->StartCutscene("test2");
	}

	else if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		App->cutscene_manager->StartCutscene("test3");
	}

	else if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		App->cutscene_manager->StartCutscene("test4");
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate(float dt)
{
	return true;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	App->map->CleanUp();
		
	LOG("Freeing scene");

	return true;
}

void j1Scene::SceneLimits()
{
	//Camera Limits
	iPoint camera_limit;
	camera_limit.x = (-1 * App->map->data.width * App->map->data.tile_width) + App->render->camera.w;
	camera_limit.y = (-1 * App->map->data.height * App->map->data.tile_height) + App->render->camera.h;

	if (App->render->camera.x > 0) { App->render->camera.x = 0; }
	else if (App->render->camera.x < camera_limit.x) { App->render->camera.x = camera_limit.x; }
	if (App->render->camera.y > 0) { App->render->camera.y = 0; }
	else if (App->render->camera.y < camera_limit.y) { App->render->camera.y = camera_limit.y; }

	//Player Limits
	/*iPoint player_limit;
	player_limit.x = App->map->data.width * App->map->data.tile_width - 32;
	player_limit.y = App->map->data.height * App->map->data.tile_height - 48;

	if (App->characters->player.x < 0) { App->characters->player.x = 0; }
	else if (App->characters->player.x > player_limit.x) { App->characters->player.x = player_limit.x; }
	if (App->characters->player.y < 0) { App->characters->player.y = 0; }
	else if (App->characters->player.y > player_limit.y) { App->characters->player.y = player_limit.y; }*/
}







