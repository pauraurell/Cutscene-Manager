#ifndef __j1CUTSCENEMANAGER_H__
#define __j1CUTSCENEMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"


class j1CutsceneManager : public j1Module
{
public:

	j1CutsceneManager();

	// Destructor
	virtual ~j1CutsceneManager();

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

};

#endif // __j1SCENE_H__