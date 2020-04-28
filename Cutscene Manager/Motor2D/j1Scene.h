#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "j1Timer.h"


#define COORDS(a) a+3000 

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Check camera and player limits
	void SceneLimits();


public:
	p2SString current_level;

	iPoint mouse_position;
	iPoint map_coordinates;

};

#endif // __j1SCENE_H__