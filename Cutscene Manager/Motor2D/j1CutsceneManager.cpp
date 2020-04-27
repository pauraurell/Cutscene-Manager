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