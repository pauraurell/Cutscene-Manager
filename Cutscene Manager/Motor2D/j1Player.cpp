#include "j1Player.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"


j1Player::j1Player() : j1Module()
{
	name.create("player");
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	return true;
}

bool j1Player::Start()
{
	texture = App->tex->Load("Assets/textures/TestSprite.png");

	position.x = 84;
	position.y = 520;

	return true;
}

bool j1Player::PreUpdate(float dt)
{
	return true;
}


bool j1Player::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		position.x -= 3;
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += 3;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= 3;	
	}

	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += 3;
	}

	LOG("%d, %d", position.x, position.y);
	return true;
}

bool j1Player::PostUpdate(float dt)
{

	App->render->Blit(texture, position.x, position.y);
	return true;
}

bool j1Player::CleanUp()
{
	App->tex->UnLoad(texture);

	return true;
}
