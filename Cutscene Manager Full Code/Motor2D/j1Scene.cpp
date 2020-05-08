#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
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

	current_level = "TestMap.tmx";
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

	//Camera following the player and limits
	App->render->camera.x = -player.x + App->win->width / 2;
	App->render->camera.y = -player.y + App->win->height / 2;
	SceneLimits();

	//TODO 6: Now we just have to start the cutscene that we want if it is in a certain position. To do that we will see
	// if the player is on a certain tile we will define in the Tiled map. The layers and properties are allready done and 
	// properly loaded in map.cpp so you just have to touch this module.

	iPoint MapPos;
	list<MapLayer*>::iterator Layer_list;
	MapLayer* layer;

	for (Layer_list = App->map->data.layers.begin(); Layer_list != App->map->data.layers.end(); ++Layer_list)
	{
		layer = *Layer_list;
		MapPos = App->map->WorldToMap(App->characters->player_pos.x, App->characters->player_pos.y);
		if (layer->Get(MapPos.x, MapPos.y) == 2)
		{
			if (layer->returnPropValue("Cutscene") == 1) 
			{
				App->cutscene_manager->StartCutscene("SampleCutscene1");
			}		
			else if (layer->returnPropValue("Cutscene") == 2)
			{
				App->cutscene_manager->StartCutscene("SampleCutscene2");
			}
		}
	}

	//Draw the map
	App->map->Draw();
	map_coordinates = App->map->WorldToMap(mouse_position.x, mouse_position.y);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->cutscene_manager->StartCutscene("test");
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
}







